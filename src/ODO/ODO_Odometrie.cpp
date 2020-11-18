/*
 * ODO_Odometrie.cpp
 *
 *  Created on: 17 nov. 2020
 *      Author: thomas
 */

#include "ODO_Odometrie.hpp"
#include "COD_SerialCodeurManager.hpp"

ODO::COdometrie::COdometrie(COF::CStrategieDeplacement* p_strategieDeplacement, COF::CConfigurationRobot* p_configStruct, COD::CSerialCodeurManager* p_codeursManager)
{
	m_odometrieStruct = {0};
	m_strategieDepalcement = p_strategieDeplacement;
	m_configStruct = p_configStruct;
	m_codeursManager = p_codeursManager;

	if (m_strategieDepalcement == NULL || m_codeursManager == NULL || m_configStruct == NULL) {
		printf("Pointeur NULL !!!!!");
		exit(1);
	}
}

ODO::COdometrie::~COdometrie()
{

}

void ODO::COdometrie::initialiser()
{
	m_odometrieStruct.xDepart = m_strategieDepalcement->getStrategieDeplacement(0)->x;
	m_odometrieStruct.yDepart = m_strategieDepalcement->getStrategieDeplacement(0)->y;
	m_odometrieStruct.angleConsigne = m_strategieDepalcement->getStrategieDeplacement(0)->angle;
	m_odometrieStruct.vitesse = 0;
}

void ODO::COdometrie::reorientation()
{
	if (abs(m_odometrieStruct.angleConsigne - m_odometrieStruct.angleActuel) > 180) {
		if (m_odometrieStruct.angleActuel > 0) {
			m_odometrieStruct.angleActuel -= 360;
		}
		else if (m_odometrieStruct.angleActuel < 0) {
			m_odometrieStruct.angleActuel += 360;
		}
	}
}

void ODO::COdometrie::calculConsigne()
{
   /* Pour savoir si la cible est à gauche ou à droite du robot, on
	* calcule le sinus de l'angle entre la cible et le robot
	* sin = Opp/Hyp, on a opp et on retrouve hyp grâce à Pythagore
	* Sinus auxiliaire pour savoir où se trouve la cible par
	* rapport au robot
	*/
	float sinAux = (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart) / (sqrt((m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) * (m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) + (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart) * (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart)));
	float aco = acos((m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) / ((sqrt((m_odometrieStruct.xArrive - m_odometrieStruct.xDepart)*(m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) + (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart)*(m_odometrieStruct.yArrive - m_odometrieStruct.yDepart))))) * 360 /(2 * M_PI);

	// On change la consigne selon le fait que la cible soit à gauche
	// (-aco) ou a droite (+aco) du robot
	m_odometrieStruct.angleConsigne = sinAux > 0 ? -aco : +aco;
    reorientation();
}

void ODO::COdometrie::miseAJourPosition()
{
	// Lecture et reinitialisation des codeurs
	m_codeursManager->readAndReset();
	m_odometrieStruct.nbTickDroit = m_codeursManager->getRightTicks();
	m_odometrieStruct.nbTickGauche = m_codeursManager->getLeftTicks();

	// Calcul de la différence du nombre de tic entre chaque codeur (car
	// différent si on ne roule pas droit) qu'on converti en angle
	m_odometrieStruct.orientation = (m_configStruct->getConfRobot().coeffAngleRoueGauche * m_odometrieStruct.nbTickGauche - m_configStruct->getConfRobot().coeffAngleRoueDroite * m_odometrieStruct.nbTickDroit) + m_odometrieStruct.orientationDerive;
	m_odometrieStruct.orientationDerive = m_odometrieStruct.orientation;


	// Calcul de la distance parcourue
	m_odometrieStruct.distanceParcourue = (m_configStruct->getConfRobot().coeffLongueurRoueGauche * m_odometrieStruct.nbTickGauche + m_configStruct->getConfRobot().coeffLongueurRoueDroite * m_odometrieStruct.nbTickDroit) / 2;

	// Calcul de la derive en vitesse
	m_odometrieStruct.vitesse = m_odometrieStruct.distanceParcourue - m_odometrieStruct.distancePrecedent;
	m_odometrieStruct.distancePrecedent = m_odometrieStruct.distanceParcourue;

	m_odometrieStruct.xDelta = -m_odometrieStruct.vitesse*(sin(m_odometrieStruct.orientation));
	m_odometrieStruct.yDelta =  m_odometrieStruct.vitesse*(cos(m_odometrieStruct.orientation));

	m_odometrieStruct.xArrive = m_odometrieStruct.xArrive + m_odometrieStruct.xDelta;
	m_odometrieStruct.yArrive = m_odometrieStruct.yArrive + m_odometrieStruct.yDelta;
}



