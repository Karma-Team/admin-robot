/*
 * ASV_Asserv.cpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ASV_Asserv.hpp"

ASV::CAsserv::CAsserv(MOT::CMoteurManager* p_moteurManager, COF::SConfigRobot* p_configStruct, ODO::COdometrie* p_odometrie)
{
	m_configStruct = p_configStruct;
	m_moteurManager = p_moteurManager;
	m_odometrie = p_odometrie;
	m_structPid = {0};
	m_cmdMoteur = {0};

	if (m_odometrie == NULL || m_moteurManager == NULL || m_configStruct == NULL) {
		printf("Pointeur NULL !!!!!");
		exit(1);
	}
}

ASV::CAsserv::~CAsserv()
{
	// rien a faire
}

void ASV::CAsserv::asservirVersCible()
{
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

	calculCmdMoteur();
	appliquerCmdMoteur();
}

void ASV::CAsserv::calculCmdMoteur()
{
	m_cmdMoteur.cmdMoteurDroit = m_structPid.orientationPid + m_structPid.distancePid;
	m_cmdMoteur.cmdMoteurGauche = m_structPid.orientationPid + m_structPid.distancePid;

	verifOverflowCommandes();

	m_cmdMoteur.cmdMoteurDroit *= m_odometrie->getOdometrieVariables()->vitesse / 100;
	m_cmdMoteur.cmdMoteurGauche *= m_odometrie->getOdometrieVariables()->vitesse / 100;

	appliquerCmdMoteur();
}

void ASV::CAsserv::verifOverflowCommandes()
{
	if (m_cmdMoteur.cmdMoteurGauche < -255) m_cmdMoteur.cmdMoteurGauche = -255;
	else if(m_cmdMoteur.cmdMoteurGauche > 255) m_cmdMoteur.cmdMoteurGauche = 255;

	if (m_cmdMoteur.cmdMoteurDroit < -255) m_cmdMoteur.cmdMoteurDroit = -255;
	else if (m_cmdMoteur.cmdMoteurDroit > 255) m_cmdMoteur.cmdMoteurDroit = 255;
}

void ASV::CAsserv::appliquerCmdMoteur()
{
	if (true)
	{ // Marche avant

			if (m_cmdMoteur.cmdMoteurGauche < 0)
				m_moteurManager->gauchePWM(abs(m_cmdMoteur.cmdMoteurGauche), 0);
			else
				m_moteurManager->gauchePWM(0, m_cmdMoteur.cmdMoteurGauche);

			if (m_cmdMoteur.cmdMoteurDroit < 0)
				m_moteurManager->droitePWM(abs(m_cmdMoteur.cmdMoteurDroit), 0);
			else
				m_moteurManager->droitePWM(0, m_cmdMoteur.cmdMoteurDroit);
	}

	else
	{ // Marche arrière

			if (m_cmdMoteur.cmdMoteurDroit < 0)
				m_moteurManager->gauchePWM(0, abs(m_cmdMoteur.cmdMoteurDroit));
			else
				m_moteurManager->gauchePWM(m_cmdMoteur.cmdMoteurDroit, 0);

			if (m_cmdMoteur.cmdMoteurGauche < 0)
				m_moteurManager->droitePWM(0, abs(m_cmdMoteur.cmdMoteurGauche));
			else
				m_moteurManager->droitePWM(m_cmdMoteur.cmdMoteurGauche, 0);
	}
}

