/*
 * remote.cpp
 *
 *  Created on: 29 mars 2020
 *      Author: thomas
 */

#include <iostream>
#include <iomanip>      // std::setprecision
#include "STR_Remote.hpp"
#include "COD_SerialCodeurManager.hpp"
#include "COD_ThreadCodeurManager.hpp"
#include "COF_Strategie.hpp"
#include "ASV_Asserv.hpp"
#include "MOT_MoteurPWM.hpp"

using namespace std;

STR::CRemote::CRemote(MOT::CMoteurManager *p_moteurManager, COD::CThreadCodeurManager* p_codeursManager, COF::SConfigRobot* p_configStruct)
{
	m_moteurManager = p_moteurManager;
	m_codeursManager = p_codeursManager;
	m_configStruct = p_configStruct;
	m_vitesse = 0;

	if(m_moteurManager == NULL || m_codeursManager == NULL || m_configStruct == NULL)
	{
		printf("Pointeur NULL !!!!!");
		exit(1);
	}
}

STR::CRemote::~CRemote()
{
	// rien a faire
}

int STR::CRemote::startRemote()
{
	int cmd;
	int lastMove = 'a';
	int vitesse = 150;
	int tmp;

	printCommands();

	system ("/bin/stty raw");

	while((cmd=getchar())!= '.')
	{

		putchar(cmd);

		cout << endl;

		system ("/bin/stty cooked");

		switch(cmd)
		{
			case 'a':
			case 'z':
			case 's':
			case 'q':
			case 'd':
			case 'b':
			case 'c':
			{
				askedMove(cmd, vitesse);
			}
			break;

			case '+':
			case '-':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '*':
			{
				tmp = askedSpeed(cmd);
				vitesse = tmp;
				askedMove(lastMove, vitesse);
			}
			break;

			case 'e':
			{
				printValeurCodeur();
			}
			break;

			case 't':
			{
				testCodeurValue();
			}
			break;

			case 'w':
			{
				asservTest();
			}
			break;

			default:
				// rien a faire
			break;


		}

		m_moteurManager->dummy = true;

		m_moteurManager->dummy = false;


		system ("/bin/stty raw");

	}
	system ("/bin/stty cooked");

	sleep(1);
	m_moteurManager->stop();
	m_moteurManager->apply();


	return 0;
}

bool STR::CRemote::askedMove(int p_cmd, int p_vitesse)
{

	bool ServoUtiliser = false;

	switch(p_cmd)
	{
		case 'z': //haut
			MOT::CMoteurPWM::inst()->setMoteurSpeed(0, p_vitesse, 0, p_vitesse);
		break;
		case 's': //bas
			MOT::CMoteurPWM::inst()->setMoteurSpeed(p_vitesse, 0, p_vitesse, 0);
		break;
		case 'q'://gauche
			MOT::CMoteurPWM::inst()->setMoteurSpeed(p_vitesse, 0, 0, p_vitesse);
		break;
		case 'd': //droite
			MOT::CMoteurPWM::inst()->setMoteurSpeed(0, p_vitesse, p_vitesse, 0);
		break;
		case 'a': //stop
			MOT::CMoteurPWM::inst()->setMoteurSpeed(0, 0 ,0, 0);
		break;
		case 'b': //stop
			MOT::CMoteurPWM::inst()->setMoteurSpeed(0, 0, 0, p_vitesse);
		break;
		case 'n': //stop
			MOT::CMoteurPWM::inst()->setMoteurSpeed(0, p_vitesse, 0, 0);
		break;
		case 'i': //servoAction

		break;

		default:
			return false;
	}
	if(ServoUtiliser == false)
		m_moteurManager->apply();

	return true;
}


void STR::CRemote::printCommands()
{
	printf("\n");
	printf("Z Q S D : déplacement\n");
	printf("B C : Rotation sur une roue\n");
	printf("A : Arrêt du robot\n");
	printf("E : Récupérer les valeurs des codeurs (fausse la génération de points !)\n");
	printf("T : Test le retour des codeurs)\n");
	printf("W : Test Asserv");
	printf("0-9-* : Réglage de la vitesse du robot de 0 à 100\n");
	printf(" . puis CTRL-C : Quitter\n");
}

int STR::CRemote::askedSpeed(int p_cmd)
{
	switch(p_cmd)
	{
		case '+':
			printf("Vitesse argmente : %i\n", m_vitesse+5);
			return m_vitesse = m_vitesse+5;
		case '-':
			printf("Vitesse diminue : %i\n",m_vitesse-5);
			return m_vitesse = m_vitesse-5;
		case '0':
			return 0;
		case '1':
			return 10;
		case '2':
			return 20;
		case '3':
			return 30;
		case '4':
			return 40;
		case '5':
			return 50;
		case '6':
			return 60;
		case '7':
			return 70;
		case '8':
			return 80;
		case '9':
			return 90;
		case '*':
			return 100;
	}
	return -1;
}

void STR::CRemote::printValeurCodeur()
{
	printf("CG:%d, CD:%d",m_codeursManager->getTicksGauche(), m_codeursManager->getTicksDroit());
	m_codeursManager->reset();
}

void STR::CRemote::testCodeurValue()
{
	while(true)
	{
		printf("CG:%d, CD:%d",m_codeursManager->getTicksGauche(), m_codeursManager->getTicksDroit());
	}
}

void STR::CRemote::asservTest()
{
	int indexStrategie = 0;
	COF::CStrategieDeplacement csvStrategieDeplacement = COF::CStrategieDeplacement("StDeplacement.csv");
	COF::SStrategieDeplacement* pointStrategieDeplacement = csvStrategieDeplacement.getStrategieDeplacement(indexStrategie);
	ODO::COdometrie odometrie = ODO::COdometrie(pointStrategieDeplacement, m_configStruct, m_codeursManager);
	odometrie.initialiser();
	
	ASV::CAsserv asserv = ASV::CAsserv(m_moteurManager, m_configStruct, &odometrie);
	
	indexStrategie++;
	pointStrategieDeplacement = csvStrategieDeplacement.getStrategieDeplacement(indexStrategie);
	
	while(1)//indexStrategie != csvStrategieDeplacement.getSizeStrategie())
	{
		odometrie.setStrategieDeplacement(pointStrategieDeplacement);
		odometrie.miseAJourPosition();
		odometrie.calculConsigneDeplacement();
		odometrie.debug();
		if(asserv.asservirVersCible())
		{
			indexStrategie++;
			pointStrategieDeplacement = csvStrategieDeplacement.getStrategieDeplacement(indexStrategie);
		}
		asserv.debug();
		usleep(10000);
	}
}


