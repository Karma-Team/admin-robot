/*
 * ODO_Odometrie.cpp
 *
 *  Created on: 17 nov. 2020
 *      Author: thomas
 */

#include "ODO_Odometrie.hpp"
#include "COD_SerialCodeurManager.hpp"
#include "COD_ThreadCodeurManager.hpp"

using namespace std;


ODO::COdometrie::COdometrie(COF::SStrategieDeplacement* p_strategieDeplacement, COF::SConfigRobot* p_configStruct, COD::CThreadCodeurManager* p_codeursManager)
{
	m_odometrieStruct = {0};
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
	m_odometrieStruct.xActuel = m_strategieDepalcement->x;
	m_odometrieStruct.yActuel = m_strategieDepalcement->y;
	m_odometrieStruct.angleConsigne = m_strategieDepalcement->angle;
	m_odometrieStruct.vitesse = 0;
}

void ODO::COdometrie::setStrategieDeplacement(COF::SStrategieDeplacement* p_strategieDepalcement)
{
	m_strategieDepalcement = p_strategieDepalcement;
}

void ODO::COdometrie::miseAJourPosition()
{
	// Lecture et reinitialisation des codeurs
	m_odometrieStruct.nbTickDroit = m_codeursManager->getTicksDroit();
	m_odometrieStruct.nbTickGauche = m_codeursManager->getTicksGauche();
	m_codeursManager->reset();

	// Calcul de l'orientation du robot actuel
	m_odometrieStruct.orientationActuel = (m_configStruct->coeffAngleRoueGauche * m_odometrieStruct.nbTickGauche - m_configStruct->coeffAngleRoueDroite * m_odometrieStruct.nbTickDroit) - m_odometrieStruct.orientationDerive;
	m_odometrieStruct.orientationDerive = m_odometrieStruct.orientationActuel;

	// Calcul de la distance parcourue
	m_odometrieStruct.distanceParcourue += (m_configStruct->coeffLongueurRoueGauche * m_odometrieStruct.nbTickGauche + m_configStruct->coeffLongueurRoueDroite * m_odometrieStruct.nbTickDroit) / 2;

	// Calcul de la vitesse de deplacement
	m_odometrieStruct.vitesse = m_odometrieStruct.distanceParcourue - m_odometrieStruct.distancePrecedent;
	m_odometrieStruct.distancePrecedent = m_odometrieStruct.distanceParcourue;
	
	// Actualisation de la position X et Y du robot
	m_odometrieStruct.xDelta = -m_odometrieStruct.vitesse*(sin(m_odometrieStruct.orientationActuel));
	m_odometrieStruct.yDelta =  m_odometrieStruct.vitesse*(cos(m_odometrieStruct.orientationActuel));
	
	m_odometrieStruct.xActuel = m_odometrieStruct.xActuel + m_odometrieStruct.xDelta;
	m_odometrieStruct.yActuel = m_odometrieStruct.yActuel + m_odometrieStruct.yDelta;
}

void ODO::COdometrie::calculConsigneDeplacement()
{
	// Recuperation de la position de destination
	m_odometrieStruct.xArrive = m_strategieDepalcement->x;
	m_odometrieStruct.yArrive = m_strategieDepalcement->y;
	
	// Calcul de la distance qui separe le robot de la cible
	m_odometrieStruct.distanceConsigne = sqrt(((m_odometrieStruct.xArrive - m_odometrieStruct.xActuel) * (m_odometrieStruct.xArrive - m_odometrieStruct.xActuel)) + ((m_odometrieStruct.yArrive - m_odometrieStruct.yActuel) * (m_odometrieStruct.yArrive - m_odometrieStruct.yActuel)));
	
	// Calcul de l'orientation du robot pour faire face a la cible
	float xdistance = (m_odometrieStruct.xArrive - m_odometrieStruct.xActuel);
	float ydistance = (m_odometrieStruct.yArrive - m_odometrieStruct.yActuel);

	if((xdistance != 0) && (ydistance != 0))
	{
		m_odometrieStruct.orientationVersCible = atan(xdistance/ydistance);
	}
	else
	{
		m_odometrieStruct.orientationVersCible = 0;
	}

	m_odometrieStruct.orientationConsigne -= m_odometrieStruct.orientationVersCible - m_odometrieStruct.orientationActuel;
}

ODO::SOdometrieVariables* ODO::COdometrie::getOdometrieVariables()
{
	return &m_odometrieStruct;
}

void ODO::COdometrie::debug()
{
	cout << endl;
	cout << "tickGauche : " << m_odometrieStruct.nbTickGauche << " tickDroit : "  << m_odometrieStruct.nbTickDroit << endl;
	cout << "orientationActuel " << m_odometrieStruct.orientationActuel << endl;
	cout << "distanceParcourue " << m_odometrieStruct.distanceParcourue << endl;
	cout << "vitesse " << m_odometrieStruct.vitesse << endl;
	cout << "xActuel " << m_odometrieStruct.xActuel << endl;
	cout << "yActuel " << m_odometrieStruct.yActuel << endl;
	cout << "xArrive " << m_odometrieStruct.xArrive << endl;
	cout << "yArrive " << m_odometrieStruct.yArrive << endl;
	cout << "distanceConsigne " << m_odometrieStruct.distanceConsigne << endl;
	cout << "orientationVersCible " << m_odometrieStruct.orientationVersCible << endl;
	cout << "orientationConsigne " << m_odometrieStruct.orientationConsigne << endl;
	cout << endl;
}
