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
	m_structPid = {0};
	m_strategieDepalcement = p_strategieDeplacement;
	m_configStruct = p_configStruct;
	m_codeursManager = p_codeursManager;
	m_index = 0;
	m_cmdMoteurDroit = 0;
	m_cmdMoteurGauche = 0;

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
	m_odometrieStruct.xActuel = m_strategieDepalcement->getStrategieDeplacement(m_index)->x;
	m_odometrieStruct.yActuel = m_strategieDepalcement->getStrategieDeplacement(m_index)->y;
	m_odometrieStruct.angleConsigne = m_strategieDepalcement->getStrategieDeplacement(m_index)->angle;
	m_odometrieStruct.vitesse = 0;
}

void ODO::COdometrie::miseAJourPosition()
{
	// Lecture et reinitialisation des codeurs
	m_codeursManager->readAndReset();
	m_odometrieStruct.nbTickDroit = m_codeursManager->getRightTicks();
	m_odometrieStruct.nbTickGauche = m_codeursManager->getLeftTicks();

	// Calcul de l'orientation du robot actuel
	m_odometrieStruct.orientationActuel = (m_configStruct->getConfRobot().coeffAngleRoueGauche * m_odometrieStruct.nbTickGauche - m_configStruct->getConfRobot().coeffAngleRoueDroite * m_odometrieStruct.nbTickDroit) + m_odometrieStruct.orientationDerive;
	m_odometrieStruct.orientationDerive = m_odometrieStruct.orientationActuel;

	// Calcul de la distance parcourue
	m_odometrieStruct.distanceParcourue = (m_configStruct->getConfRobot().coeffLongueurRoueGauche * m_odometrieStruct.nbTickGauche + m_configStruct->getConfRobot().coeffLongueurRoueDroite * m_odometrieStruct.nbTickDroit) / 2;

	// Calcul de la vitesse de deplacement
	m_odometrieStruct.vitesse = m_odometrieStruct.distanceParcourue - m_odometrieStruct.distancePrecedent;
	m_odometrieStruct.distancePrecedent = m_odometrieStruct.distanceParcourue;
	
	// Actualisation de la position X et Y du robot
	m_odometrieStruct.xDelta = -m_odometrieStruct.vitesse*(sin(m_odometrieStruct.orientation));
	m_odometrieStruct.yDelta =  m_odometrieStruct.vitesse*(cos(m_odometrieStruct.orientation));
	
	m_odometrieStruct.xActuel = m_odometrieStruct.xActuel + m_odometrieStruct.xDelta;
	m_odometrieStruct.yActuel = m_odometrieStruct.yActuel + m_odometrieStruct.yDelta;
}

void ODO::COdometrie::calculConsigneDeplacement()
{
	// Recuperation de la position de destination
	m_odometrieStruct.xArrive = m_strategieDepalcement->getStrategieDeplacement(m_index)->x;
	m_odometrieStruct.yArrive = m_strategieDepalcement->getStrategieDeplacement(m_index)->y;
	
	// Calcul de la distance qui separe le robot de la cible
	m_odometrieStruct.distanceConsigne = sqrt(((m_odometrieStruct.xArrive - m_odometrieStruct.xActuel) * (m_odometrieStruct.xArrive - m_odometrieStruct.xActuel)) + ((m_odometrieStruct.yArrive - m_odometrieStruct.yActuel) * (m_odometrieStruct.yArrive - m_odometrieStruct.yActuel)));
	
	// Calcul de l'orientation du robot pour faire face a la cible
	m_odometireStruct.orientationVersCible = arctg((m_odometrieStruct.xArrive - m_odometrieStruct.xActuel)/(m_odometrieStruct.yArrive - m_odometrieStruct.yActuel));
	m_odometireStruct.orientationConsigne = m_odometireStruct.orientationVersCible - m_odometireStruct.orientationActuel;
}

void ODO::COdometrie::asservirVersCible()
{
	// Calcul PID de orientation
	m_structPid.erreurOrientationKp = m_odometireStruct.orientationConsigne - m_odometrieStruct.orientationActuel;
	m_structPid.sommeErreurOrientationKi += m_structPid.erreurOrientationKp;
	m_structPid.deltaErreurOrientationKd = m_structPid.erreurOrientationKp - m_structPid.erreurOrientationPrecedente;
	m_structPid.erreurOrientationPrecedente = m_structPid.erreurOrientationKp
		
	m_structPid.orientationPid = (m_configStruct->pidKpA*m_structPid.erreurOrientationKp) + (m_configStruct->pidKdA*m_structPid.deltaErreurOrientationKd) + (m_configStruct->pidKiA*m_structPid.sommeErreurOrientationKi);
	
	// Calcul PID de la distance
	m_structPid.erreurDistanceKp = m_odometireStruct.distanceConsigne - m_odometrieStruct.distanceParcourue;
	m_structPid.sommeErreurDistanceKi += m_structPid.erreurDistanceKp;
	m_structPid.deltaErreurDistanceKd = m_structPid.erreurDistanceKp - m_structPid.erreurDistancePrecedente;
	m_structPid.erreurDistancePrecedente = m_structPid.erreurDistanceKp
		
	m_structPid.distancePid = (m_configStruct->pidKpD*m_structPid.erreurDistanceKp) + (m_configStruct->pidKdD*m_structPid.deltaErreurDistanceKd) + (m_configStruct->pidKiD*m_structPid.sommeErreurDistanceKi);
	
}



