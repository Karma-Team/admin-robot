/*#include "ASV_AsservRasp.hpp"

#include <iostream>
#include <cmath>
#include <cstdint>
#include <string>

using namespace std;

Asservissement::Asservissement(
		MoteurManager& mots,
		ICodeurManager& cods,
		const vector<Point>& pts) :
	moteurs(mots),
	codeurs(cods),
	indexPointActuel(0),
	points(pts)
{

}

void Asservissement::stop()
{
	cerr << "STOP" << endl;
	moteurs.stop();
	moteurs.apply();
}

Point Asservissement::pointActuel() const
{
	return points.at(indexPointActuel);
}

void Asservissement::autoriserPointSuivant()
{
	demandePointSuivant = false;
	pointSuivantAutorise = true;
}
void Asservissement::pointSuivant()
{

	//Demande de passage au point suivant au main
	if(!pointSuivantAutorise)
	{
		demandePointSuivant = true;
		return;
	}
	else
	{
		pointSuivantAutorise = false;
		demandePointSuivant = false;
	}

	cout << "\nPOINT ATTEINT: ";
	pointActuel().display();
	indexPointActuel++;
	suite = 0;


	if (indexPointActuel >= nbPoints())
	{
		indexPointActuel = nbPoints()-1;
		cout << "\nPlus de points\n";
		moteurs.stop();
		suite = 1;
		//return;
	}
	else
	{
		cout << "\nNOUVEAU POINT: ";
		pointActuel().display();
		distancenew = true;
		distanParcourue = 0;
	}
}

int Asservissement::nbPoints() const
{
	return points.size();
}

bool Asservissement::isFinished()
{
	if (indexPointActuel >= nbPoints())
	{
		return true;
	}
	return false;
}


void Asservissement::verifOverflowCommandes()
{

	if (cmdG < -255) cmdG = -255;
	else if(cmdG > 255) cmdG = 255;

	if (cmdD < -255) cmdD = -255;
	else if (cmdD > 255) cmdD = 255;
}


void Asservissement::reorientation()
{
	if (abs(consigne_orientation - orientation) > 180) {
		if (orientation > 0) {
			orientation -= 360;
			orientationP = orientation;
		}
		else if (orientation < 0) {
			orientation += 360;
			orientationP = orientation;
		}
	}
}

void Asservissement::initialiser(Point pt)
{
	// Initialisation des coordonnées à partir du point initial
	xC = pt.getX();
	yC = pt.getY();
	xAP = pt.getX();
	yAP = pt.getY();
	

	// Initialisation de l’orientation (premier point d’angle)
	orientation = pt.getDist();
	orientationP = pt.getDist();

	// Initialisation de la consigne
	consigne_orientation = orientation;
	consignePre = consigne_orientation;
	reorientation();
	// Initialisation de la valeur des codeurs
	comptD = 0;
	comptG = 0;

	// Initialisation des moteurs
	// TODO: commande des moteurs vitesse nulle en I2C
	cmdG = 0;
	cmdD = 0;
	cmdA = 0;

	// Initialisation
	somme_erreurA = 0;
}


void Asservissement::calculConsigne()
{
	// Pour savoir si la cible est à gauche ou à droite du robot, on
	// calcule le sinus de l'angle entre la cible et le robot

	// sin = Opp/Hyp, on a opp et on retrouve hyp grâce à Pythagore

	// Sinus auxiliaire pour savoir où se trouve la cible par
	// rapport au robot
	float sinAux = (yC - yA) / (sqrt((xC - xA) * (xC - xA) + (yC - yA) * (yC - yA)));
	float aco = acos((xC - xA) / ((sqrt((xC-xA)*(xC-xA) + (yC-yA)*(yC-yA))))) * 360 /(2 * M_PI);

	// On change la consigne selon le fait que la cible soit à gauche
	// (-aco) ou a droite (+aco) du robot
	consigne_orientation = sinAux > 0 ? -aco : +aco;
    reorientation();
	// Activation de la marche arrière si elle est demandée par le point
	if (pointActuel().getSens() == 1 && erreurP >= 0) {
		derriere = true;
		//changment du signe de la distance parcourue du a la décrémentation des codeurs en cas de marche arrière
		distanParcourue = abs(distanParcourue);
		if (consigne_orientation > 0)
			consigne_orientation -= 180;
		else
			consigne_orientation += 180;
	}
	else if(pointActuel().getSens() == 0 && erreurP >= 0 ) {
		derriere = false;
	}
	else if( pointActuel().getSens() == 1 && erreurP < 0) {
		derriere = false;
	}
	else if( pointActuel().getSens() == 0 && erreurP < 0 ) {
		derriere = true;
		if (consigne_orientation > 0)
			consigne_orientation -= 180;
		else
			consigne_orientation += 180;
	}
}


void Asservissement::asservir()
{
	nbAsservCalled++;
	//printf("asservir : %d\n", nbAsservCalled);//debug

	// Si on a plus de points on return
	if (indexPointActuel >= nbPoints())
	{
		return;
	}

	// dOrientation = angle effectué par le robot

	// Lecture et réinitialisation des codeurs
	codeurs.readAndReset();

	// Lecture des valeurs lues depuis les codeurs pour connaître la variation
	// entre deux appels de la fonction d'asservissement.
	comptG = codeurs.getLeftTicks();
	comptD = codeurs.getRightTicks();
	int saveG = comptG;
	int saveD = comptD;
	// Calcul de la différence du nombre de tic entre chaque codeur (car
	// différent si on ne roule pas droit) qu'on converti en angle
	float dOrientation = CoeffGAngl * comptG - CoeffDAngl * comptD;
	orientation += dOrientation;

	// orientationP = moyenne des angles pour connaître le cap exact
	dAngl = (orientation + orientationP) / 2;
	orientationP = orientation;   // mise à jour de orientationP

	// Calcul de la distance parcourue par le centre de la base roulante grâce
	// à une conversion nombre de tic / distance en mm.
	dDepl = (CoeffDLong * comptD + CoeffGLong * comptG) / 2;
	distanParcourue += dDepl;
	
	//cout << "Coefs " << CoeffGLong << " " << CoeffDLong << " " << CoeffGAngl << " " << CoeffDAngl << endl;

	// Remise à zero de la valeur lue par les codeurs
	// TODO: utile ?
	comptG = 0;
	comptD = 0;

	//
	// POSITION
	//
	// Maintenant qu'on connaît la variation de cap et de distance, on peut
	// calculer la variation en x et y de notre robot.  En effet, grâce aux
	// formules de trigonométrie élémentaires, (sinus = opposé / hypoténuse,
	// cosinus = adjacent / hypoténuse) On peut calculer la variation en x et y
	// de notre position.
	//
	// On en déduit donc les nouvelles coordonnées du robot !

	// Valeur relative de x et y (en fonction du point de départ du robot)
	// Valeur relative de x et y (en fonction du point de départ du robot)
	float dx = 0.0;
	float dy = 0.0;

	dx = dDepl * cos(1*dAngl * (2 * M_PI / 360));
	dy = dDepl * sin(-1*dAngl * (2 * M_PI / 360));

	// Valeur absolue de x et y, xAP et yAP sont les points de départ du robot
	// (pour ce loop)
	xA = xAP + dx;
	yA = yAP + dy;

	xAP = xA;
	yAP = yA;


	
	calculConsigne();
	reorientation();
	
	// Si on a un déplacement
	if (pointActuel().getCoeff() != 0.0)
	{

		// Le principal problème rencontré cette année pour le déplacement est
		// la gestion d'un angle de 180°. En effet, un angle de 180 ou de -180°
		// est identique pour nous pauvre humain, mais pour un robot se
		// tournant soit vers la gauche soit vers la droite ces deux angles
		// sont complètement différents !  Pour éviter d'avoir un robot
		// "danseur" on garde en mémoire la consigne précédente, ainsi si le
		// robot passe de 180 à - 180 on le détecte et on corrige cette erreur
		// en changeant le signe.

		if (abs(consignePre - consigne_orientation) > 200){
			// Bug des 180 !!!!!
			if(consigne_orientation < 0)
				consigne_orientation += 360;
			else
				consigne_orientation -= 360;
	}

		
		consignePre = consigne_orientation;
	}


	reorientation();

		//
	// DISTANCE
	//
	// Maintenant qu'on connaît la position de notre robot, on peut déterminer
	// la distance restante à parcourir. Grâce au théorème de Pythagore : Dans
	// un triangle rectangle : hypoténuse² = somme des côtés élevé au carré
	// (pour les incultes).

	distanceDeuxPoints = sqrt((xA - xC) * (xA - xC) + (yA - yC) * (yA - yC));
	if(distancenew == true)
	{
		distanceAFaire = distanceDeuxPoints;
		distancenew = false;
		//cout << "distance a faire :" << distanceAFaire << endl;
	}

	erreurP = pointActuel().getCoeff() * (distanceAFaire - distanParcourue);

		if(false)
		{
			cout << "erreurP :" << erreurP << endl;
			cout << "distanceAFaire :" << distanceAFaire << endl;
			cout << "distanParcourue :" << distanParcourue << endl;
			cout << "distanceDeuxPoints :" << distanceDeuxPoints << endl;

		}
	

	// Maintenant qu'on connaît l'angle désiré et la distance, on peut
	// déterminer si le point est atteint ou non. Pour cela, on compare la
	// distance au point cible par rapport au seuil qu'on a fixé dans la classe
	// Point.  De plus, comme on peut aussi demander au robot de tourner sur
	// lui-même d'un certain angle (si le Coeff vaut 0) alors il faut tester
	// que l'erreur est inférieure au seuil.  Si c'est le cas, on passe au
	// point suivant (s'il existe, sinon on s'arrête).
	//
	// On gère aussi ici si, lors d'un simple asservissement en angle, le robot
	// s'est suffisamment tourné ou non.  On gère aussi l'attente ou non d'une
	// autorisation de la carte à changer de point. On voit qu'on à deux types
	// d'attente, si on attend une autorisation et qu'on reçoit la valeur 1, on
	// cherche quand même à atteindre le point, si on reçoit 2 on change de
	// point dans tous les cas.
	//

	//bool distanceOK = pointActuel().getCoeff() != 0 && distanceDeuxPoints < pointActuel().getDist();//methode1
	bool angleOK = (abs(erreurA) < 2 && pointActuel().getCoeff() == 0.0);
	bool distanceOK = (pointActuel().getCoeff() != 0.0 && abs(erreurP)  < 15);


	if (distanceOK || angleOK )
		if( suite == 0)
				suite = 1;


	if(suite == 2)
	{
		// Changement de point
		pointSuivant();

		if (indexPointActuel < nbPoints()) {


			// Calcul de pente d'accélération
			if (pointActuel().getVitesse() < 50)
			{
				PenteAcc=10;
			}
			else
			{
				PenteAcc=50;
			}

			xC = pointActuel().getX();
			yC = pointActuel().getY();

			calculConsigne();

			consignePre = consigne_orientation;

			reorientation();
		}
	}

	// Cette partie du programme permet au robot, si le coefficient en distance
	// est nul, de tourner sur lui-même d'un angle égal au coefficient
	// normalement prévu pour la distance d'arrêt au point.

    if (pointActuel().getCoeff() == 0.0 )//|| (pointActuel().getCoeff() != 0.0 && pointActuel().getAttente() == 1))
	{
		consigne_orientation = pointActuel().getDist();
		reorientation();
	}

	somme_erreurP += erreurP;
	float delta_erreurP = erreurP - erreur_precedenteP; // Dérivée de l'erreur
	erreur_precedenteP = erreurP;

	cmdP =  kpP * erreurP + kdP * delta_erreurP + kiP * somme_erreurP;

	if(erreurP < 0)
		{
			//derriere = true;
			distanceDepasser = true;
			//cout << "marche arriere erreurP < 0" << endl;
			//cout << "distanceDepasser : " << distanceDepasser << endl;
			cmdG = -cmdP;
		}
		else
		{
			//derriere = false;7
			distanceDepasser = false;
			//cout << "marche avant erreurP > 0" << endl;
			//cout << "distanceDepasser : " << distanceDepasser << endl;
			cmdG = cmdP;
		}

	//cmdG = pointActuel().getCoeff() * distanceDeuxPoints;//methode 1
	cmdD = cmdG;

	erreurA = consigne_orientation - orientation;

	if (debug) {
		cerr << "On a une orientation de " << orientation << endl;
		cerr << "On veut une orientation de " << consigne_orientation << endl;
	}
	somme_erreurA += erreurA;
	float delta_erreurA = erreurA - erreur_precedenteA; // Dérivée de l'erreur
	erreur_precedenteA = erreurA;
	
	if(pointActuel().getCoeff() == 0.0)
	{
		cmdA =  pointActuel().getAcc() * kpA * erreurA  + kdA * delta_erreurA + kiA*somme_erreurA;
	}
	else 
	{
		cmdA =  pointActuel().getAcc() * kpD * erreurA  + kdD * delta_erreurA + kiD*somme_erreurA;
	}
	
	
	 // En ligne droite, les deux roues roulent à la même vitesse ;)

	// Gestion de l’overflow de la commande des moteurs

	verifOverflowCommandes();

	// Ajout de la commande d’angle aux moteurs gauche et droit pour faire
	// tourner le robot

	cmdG += cmdA;
	cmdD -= cmdA;
	
		
	
	

	if (indexPointActuel < nbPoints() && detect == false) {

		// Ajustement des commandes (encore…)
		//
		// TODO: Appeler juste une seule fois verifOverflow au lieu de deux et
		// vérifier que la commande des deux moteurs donne toujours l’angle
		// voulu

		verifOverflowCommandes();

		// Calcul de la pente d’accélération
		// PenteAcc est un pourcentage, 10% ou 50% selon la vitesse initiale

		if (PenteAcc < pointActuel().getVitesse()) {
			PenteAcc += pointActuel().getAcc();
		}

		cmdD *= PenteAcc / 100;
		cmdG *= PenteAcc / 100;

		if (!derriere) { // Marche avant

			if (cmdG < 0) moteurs.gauchePWM(abs(cmdG), 0);
			else moteurs.gauchePWM(0, cmdG);

			if(cmdD < 0) moteurs.droitePWM(abs(cmdD), 0);
			else moteurs.droitePWM(0, cmdD);

		} else { // Marche arrière

			if (cmdD < 0) moteurs.gauchePWM(0, abs(cmdD));
			else moteurs.gauchePWM(cmdD, 0);

			if(cmdG < 0) moteurs.droitePWM(0, abs(cmdG));
			else moteurs.droitePWM(cmdG, 0);
		}

	} else {
		// Arrêt des moteurs
		moteurs.stop();
	}
	
	// On envoie l'ordre que l'on vient d'affecter aux moteurs
	//cout<<"cmdD : "<< cmdD << "   cmdG : "<< cmdG<<endl; 
	moteurs.apply();

	//changment du signe de la distance parcourue du a la décrémentation des codeurs en cas de marche arrière
   if(pointActuel().getSens() == 1)
		distanParcourue = -distanParcourue;
	}
	

void Asservissement::loadConfig(Config conf)
{	
	kpA = 7;
	kiA = 0.05;
	kdA = 57;

	kpP = 2;
	kiP = 0.00002;
	kdP = 9;

	kpD = 7;
	kiD = 0.02;
	kdD = 75;	
}
*/
