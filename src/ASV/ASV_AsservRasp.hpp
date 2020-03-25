/*#pragma once

#include "Point.h"
#include "Config.h"
#include "MoteurManager.h"
#include "ICodeurManager.h"
#include "ServoManager.h"

#include <vector>
#include <cstdint>
#include <thread>

// Constantes des codeurs

//Anciennes constantes
//const double CoeffGLong = 0.1965795164;
//const double CoeffDLong = 0.1965022597;
//const double CoeffGAngl = 0.037854575225517;
//const double CoeffDAngl = 0.037719928204393;




// Constantes du PID

const bool debug = false;

/// @brief Classe permettant de gérer toute la partie d’asservissement
class Asservissement
{
public:
	int suite = 0; 
	int indexPointActuel;

	// Coefs chargés depuis le fichier de config
	int kpA;
	int kiA;
	int kdA;
	
	int kpP;
	int kiP;
	int kdP;

	int kpD;
	int kiD;
	int kdD;

	int seuilMoteurs = 0;
	int sleepI2c = 0;

	float xA, yA;              // coordonnées de la position actuelle
	int sens; //sens
	
	float orientation = 0.0; //angle
	float consigne_orientation = orientation;
	float consigne_distance;

	double CoeffGLong =  0.189933523267;
	double CoeffDLong =  0.188040616773;

	double CoeffDAngl = 0.040474142559561;
	double CoeffGAngl = 0.040519524986098;

	// Ctor & dtor

	/// @brief Constructeur par défaut de l’asservissement
	///
	/// @param moteurs Les deux moteurs à gérer
	/// @param codeurs Les deux codeurs à lire
	/// @param points Liste des points à effectuer
	Asservissement(
			MoteurManager& moteurs,
			ICodeurManager& codeurs,
			const std::vector<Point>& points);

	// Méthodes

	bool isFinished();

	/// @brief Initialise le système d’asservissement
	///
	/// @param pt Point de départ
	void initialiser(Point pt);

	/// @brief Réalise l’asservissemenent du robot
	void asservir();

	void asservirPosition();

	/// @brief Point actuellement traité par l’asservissement
	///
	/// @return Le point en cours de traitement
	Point pointActuel() const;

	/// @brief Fait passer le système d’asservissement au point suivant
	void pointSuivant();

	/// @brief Calcul du nombre de points
	///
	/// @return Nombre de points
	int nbPoints() const;

	/// @brief Stoppe le robot
	void stop();

	// Méthodes factorisées depuis l’ancien code de déplacement pour plus de
	// lisibilité

	void calculConsigne();
	void reorientation();

	void verifOverflowCommandes();


	// Nombre d’appels à la méthode asservir()
	int nbAsservCalled = 0;

	// Moteurs
	MoteurManager &moteurs;
	

	//Passage au point suivant
	bool demandePointSuivant = false;
	bool pointSuivantAutorise = false;
	void autoriserPointSuivant();

	void loadConfig(Config conf);

private:

	// Attributs

	bool distancenew = true;
	float distanceAFaire = 0.0;
	float distanParcourue = 0.0;
	bool distanceDepasser = false;
	// Codeurs
	ICodeurManager &codeurs;


	// Liste des points
	
	const std::vector<Point>& points;

	// Codeurs
	int comptD = 0; // TODO: Lire codeurs en I2C
	int comptG = 0; // TODO: Lire codeurs en I2C

	// Moteurs

	int cmdG = 0; // Commande du moteur gauche
	int cmdD = 0; // Commande du moteur droit
	int cmdA = 0; // Commande envoyée pour tourner
	int cmdP = 0; // Commande position

	// Autres trucs d’asservissement

	float orientationP = 0.0;
	float consignePre = consigne_orientation;
	float erreur_precedenteA = consigne_orientation;
	float somme_erreurA = 0;
	float erreurA;

	//Asservicement position
	float erreurP = 0.0;
	float erreur_precedenteP;
	float somme_erreurP = 0; 

	bool derriere = false;
	float PenteAcc = 0;

	bool detect = false;

	// Odométrie

	float dAngl;
	float dDepl;

	float distanceDeuxPoints;  // Distance séparant le robot du point cible
	float distanceConsigne; 

	// Coordonnées de la position à t-1, correspondant ici aux coordonnées à
	// l'origine.
	float xAP = 0, yAP = 0;

	float xC = 0, yC = 0;
};
*/
