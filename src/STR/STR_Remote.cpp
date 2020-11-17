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

using namespace std;

STR::CRemote::CRemote(MOT::CMoteurManager *p_moteurManager, COD::CSerialCodeurManager* p_codeursManager, COF::SConfigRobot* p_configStruct)
{
	m_moteurManager = p_moteurManager;
	m_codeursManager = p_codeursManager;
	m_configStruct = p_configStruct;
	m_vitesse = 0;

	if(m_moteurManager == NULL or m_codeursManager == NULL or m_configStruct == NULL)
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
			m_moteurManager->gauchePWM(0, p_vitesse);
			m_moteurManager->droitePWM(0, p_vitesse);
		break;
		case 's': //bas
			m_moteurManager->gauchePWM(p_vitesse, 0);
			m_moteurManager->droitePWM(p_vitesse, 0);
		break;
		case 'q'://gauche
			m_moteurManager->gauchePWM(p_vitesse, 0);
			m_moteurManager->droitePWM(0, p_vitesse);
		break;
		case 'd': //droite
			m_moteurManager->gauchePWM(0, p_vitesse);
			m_moteurManager->droitePWM(p_vitesse, 0);
		break;
		case 'a': //stop
			m_moteurManager->gauchePWM(0, 0);
			m_moteurManager->droitePWM(0, 0);
		break;
		case 'b': //stop
			m_moteurManager->gauchePWM(p_vitesse, 0);
			m_moteurManager->droitePWM(0, 0);
		break;
		case 'n': //stop
			m_moteurManager->gauchePWM(0, 0);
			m_moteurManager->droitePWM(p_vitesse, 0);
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
			return (int)(255*10/100);
		case '2':
			return (int)(255*20/100);
		case '3':
			return (int)(255*30/100);
		case '4':
			return (int)(255*40/100);
		case '5':
			return (int)(255*50/100);
		case '6':
			return (int)(255*60/100);
		case '7':
			return (int)(255*70/100);
		case '8':
			return (int)(255*80/100);
		case '9':
			return (int)(255*90/100);
		case '*':
			return 255;
	}
	return -1;
}

void STR::CRemote::printValeurCodeur()
{
	m_codeursManager->readAndReset();
	printf("CG:%d, CD:%d",m_codeursManager->getLeftTicks(), m_codeursManager->getRightTicks());
}

void STR::CRemote::asservTest()
{
	int x,y;
	int cmd;
	while((cmd=getchar())!= '.')
	{
		printf("Entrer x: ");
		scanf("%d",&x);
		printf("Entrer y: ");
		scanf("%d",&y);

	}
}


