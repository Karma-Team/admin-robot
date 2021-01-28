/*
 * remote.cpp
 *
 *  Created on: 29 mars 2020
 *      Author: thomas
 */

#include <iostream>
#include <iomanip>      // std::setprecision
#include "STR_Remote.hpp"
#include "COD_ThreadCodeurManager.hpp"
#include "COF_Strategie.hpp"
#include "ASV_Asserv.hpp"
#include "MOT_MoteurManager.hpp"
#include "MOT_MoteurPWM.hpp"
#include "ATL_CsvAtelierDecode.hpp"

using namespace std;

STR::CRemote::CRemote(COD::CThreadCodeurManager* p_codeursManager, MOT::CMoteurPWM* p_moteurManager)
{
	m_codeursManager = p_codeursManager;
	m_moteurManager = p_moteurManager;
	m_odometrie = ODO::COdometrie(m_codeursManager);
	m_vitesse = 0; 

	if( m_codeursManager == NULL || m_moteurManager == NULL)
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
	int vitesse = 50;
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
				
			case 'f':
			{
				char fileAtelier[20] = {0};
				printf("Entrer le nom du fichier d'atelier : ");
				scanf("%s",&fileAtelier);
				ATL::CCsvAtelierDecode::inst()->readCsv(fileAtelier);
				
				// init position init du robot
				COF::SStrategieDeplacement pointStrategieDeplacement = {0,0,0,0,0,"null"};
				m_odometrie.setStrategieDeplacement(&pointStrategieDeplacement);
				m_odometrie.initialiser();
				
				// lancement de l'atelier
				ATL::CCsvAtelierDecode::inst()->lancerAtelier(m_moteurManager, &m_odometrie);
			}
			break;

			default:
				// rien a faire
			break;


		}

		system ("/bin/stty raw");

	}
	system ("/bin/stty cooked");
	
	return 0;
}

bool STR::CRemote::askedMove(int p_cmd, int p_vitesse)
{
	switch(p_cmd)
	{
		case 'z': //haut
			m_moteurManager->setMoteurSpeed(0, p_vitesse, 0, p_vitesse);
		break;
		case 's': //bas
			m_moteurManager->setMoteurSpeed(p_vitesse, 0, p_vitesse, 0);
		break;
		case 'q'://gauche
			m_moteurManager->setMoteurSpeed(p_vitesse, 0, 0, p_vitesse);
		break;
		case 'd': //droite
			m_moteurManager->setMoteurSpeed(0, p_vitesse, p_vitesse, 0);
		break;
		case 'a': //stop
			m_moteurManager->setMoteurSpeed(0, 0 ,0, 0);
		break;
		case 'b': //stop
			m_moteurManager->setMoteurSpeed(0, 0, 0, p_vitesse);
		break;
		case 'n': //stop
			m_moteurManager->setMoteurSpeed(0, p_vitesse, 0, 0);
		break;
			
		case 'i': //servoAction

		break;

		default:
			return false;
	}

	//MOT::CMoteurManager::inst()->apply();

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
	printf("F : Test Atelier File");
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
		break;
		case '-':
			printf("Vitesse diminue : %i\n",m_vitesse-5);
			return m_vitesse = m_vitesse-5;
		break;
		case '0':
			return 0;
		break;
		case '1':
			return 10;
		break;
		case '2':
			return 20;
		break;
		case '3':
			return 30;
		break;
		case '4':
			return 40;
		break;
		case '5':
			return 50;
		break;
		case '6':
			return 60;
		break;
		case '7':
			return 70;
		break;
		case '8':
			return 80;
		break;
		case '9':
			return 90;
		break;
		case '*':
			return 100;
		break;
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
	COF::CStrategieDeplacement::inst()->readCsv("StDeplacement.csv");
	COF::SStrategieDeplacement* pointStrategieDeplacement = COF::CStrategieDeplacement::inst()->getStrategieDeplacement(indexStrategie);
	
	m_odometrie.setStrategieDeplacement(pointStrategieDeplacement);
	m_odometrie.initialiser();
	
	ASV::CAsserv asserv = ASV::CAsserv(m_moteurManager, &m_odometrie);
	
	indexStrategie++;
	pointStrategieDeplacement = COF::CStrategieDeplacement::inst()->getStrategieDeplacement(indexStrategie);
	
	int  timer = 0;
	
	while(indexStrategie != COF::CStrategieDeplacement::inst()->getSizeStrategie())
	{
		while(timer < pointStrategieDeplacement->timeout && asserv.asservirVersCible(pointStrategieDeplacement))
		{
			usleep(10*1000);
			timer = timer + 10;
		}
		timer = 0;
		indexStrategie++;
		pointStrategieDeplacement = COF::CStrategieDeplacement::inst()->getStrategieDeplacement(indexStrategie);
	}
}


