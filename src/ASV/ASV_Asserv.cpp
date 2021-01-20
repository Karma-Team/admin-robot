/*
 * ASV_Asserv.cpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ASV_Asserv.hpp"
#include "MOT_MoteurManager.hpp"

using namespace std;

ASV::CAsserv::CAsserv( COF::SConfigRobot* p_configStruct, ODO::COdometrie* p_odometrie)
{
	m_configStruct = p_configStruct;

	m_odometrie = p_odometrie;
	m_structPid = {0};
	m_cmdMoteur = {0};

	if (m_odometrie == NULL || m_configStruct == NULL) {
		printf("Pointeur NULL !!!!!");
		exit(1);
	}
}

ASV::CAsserv::~CAsserv()
{
	// rien a faire
}

bool ASV::CAsserv::asservirVersCible()
{
	bool enCours = false;
	
	// Calcul PID de orientation
	m_structPid.erreurOrientationKp = m_odometrie->getOdometrieVariables()->orientationConsigne - m_odometrie->getOdometrieVariables()->orientationActuel;
	m_structPid.sommeErreurOrientationKi += m_structPid.erreurOrientationKp;
	m_structPid.deltaErreurOrientationKd = m_structPid.erreurOrientationKp - m_structPid.erreurOrientationPrecedente;
	m_structPid.erreurOrientationPrecedente = m_structPid.erreurOrientationKp;

	m_structPid.orientationPid = (m_configStruct->pidKpA*m_structPid.erreurOrientationKp) + (m_configStruct->pidKdA*m_structPid.deltaErreurOrientationKd) + (m_configStruct->pidKiA*m_structPid.sommeErreurOrientationKi);

	// Calcul PID de la distance
	m_structPid.erreurDistanceKp = m_odometrie->getOdometrieVariables()->distanceConsigne - m_odometrie->getOdometrieVariables()->distanceParcourue;
	m_structPid.sommeErreurDistanceKi += m_structPid.erreurDistanceKp;
	m_structPid.deltaErreurDistanceKd = m_structPid.erreurDistanceKp - m_structPid.erreurDistancePrecedente;
	m_structPid.erreurDistancePrecedente = m_structPid.erreurDistanceKp;

	m_structPid.distancePid = (m_configStruct->pidKpD*m_structPid.erreurDistanceKp) + (m_configStruct->pidKdD*m_structPid.deltaErreurDistanceKd) + (m_configStruct->pidKiD*m_structPid.sommeErreurDistanceKi);
	
	if(m_structPid.erreurDistanceKp > 0)
	{
		calculCmdMoteur();
	}
	else
	{
		enCours =  true;
	}


	return enCours;
}

void ASV::CAsserv::calculCmdMoteur()
{
	m_cmdMoteur.cmdMoteurDroit += m_structPid.orientationPid + m_structPid.distancePid;
	m_cmdMoteur.cmdMoteurGauche -= m_structPid.orientationPid + m_structPid.distancePid;

	verifOverflowCommandes();
	appliquerCmdMoteur();

	m_cmdMoteur.cmdMoteurDroit +=  m_structPid.distancePid;
        m_cmdMoteur.cmdMoteurGauche += m_structPid.distancePid;

	m_cmdMoteur.cmdMoteurDroit *= /*m_odometrie->getOdometrieVariables()->vitesse*/ 50 / 100;
	m_cmdMoteur.cmdMoteurGauche *= /*m_odometrie->getOdometrieVariables()->vitesse*/ 50 / 100;

	verifOverflowCommandes();
	appliquerCmdMoteur();

}

void ASV::CAsserv::verifOverflowCommandes()
{
	if (m_cmdMoteur.cmdMoteurGauche < -100) m_cmdMoteur.cmdMoteurGauche = -100;
	else if(m_cmdMoteur.cmdMoteurGauche > 100) m_cmdMoteur.cmdMoteurGauche = 100;

	if (m_cmdMoteur.cmdMoteurDroit < -100) m_cmdMoteur.cmdMoteurDroit = -100;
	else if (m_cmdMoteur.cmdMoteurDroit > 100) m_cmdMoteur.cmdMoteurDroit = 100;
}

void ASV::CAsserv::appliquerCmdMoteur()
{
	if (true)
	{ // Marche avant

			if (m_cmdMoteur.cmdMoteurGauche < 0)
				MOT::CMoteurManager::inst()->gauchePWM(abs(m_cmdMoteur.cmdMoteurGauche), 0);
			else
				MOT::CMoteurManager::inst()->gauchePWM(0, m_cmdMoteur.cmdMoteurGauche);

			if (m_cmdMoteur.cmdMoteurDroit < 0)
				MOT::CMoteurManager::inst()->droitePWM(abs(m_cmdMoteur.cmdMoteurDroit), 0);
			else
				MOT::CMoteurManager::inst()->droitePWM(0, m_cmdMoteur.cmdMoteurDroit);
	}

	else
	{ // Marche arrière

			if (m_cmdMoteur.cmdMoteurDroit < 0)
				MOT::CMoteurManager::inst()->>gauchePWM(0, abs(m_cmdMoteur.cmdMoteurDroit));
			else
				MOT::CMoteurManager::inst()->gauchePWM(m_cmdMoteur.cmdMoteurDroit, 0);

			if (m_cmdMoteur.cmdMoteurGauche < 0)
				MOT::CMoteurManager::inst()->droitePWM(0, abs(m_cmdMoteur.cmdMoteurGauche));
			else
				MOT::CMoteurManager::inst()->droitePWM(m_cmdMoteur.cmdMoteurGauche, 0);
	}
	MOT::CMoteurManager::inst()->apply();
}

void ASV::CAsserv::debug()
{
	cout << "erreurOrientationKp " << m_structPid.erreurOrientationKp ;
	cout << " erreurDistanceKp " << m_structPid.erreurDistanceKp;
	cout << " orientationPid " << m_structPid.orientationPid ;
	cout << " distancePid " << m_structPid.distancePid ;
	cout << " cmdMoteurDroit " << m_cmdMoteur.cmdMoteurDroit ;
	cout << " cmdMoteurGauche " << m_cmdMoteur.cmdMoteurGauche << endl;
}
