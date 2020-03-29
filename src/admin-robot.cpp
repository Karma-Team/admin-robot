//============================================================================
// Name        : admin-robot.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>      // std::setprecision
#include <wiringPi.h>
#include <string.h>
#include "COF_ConfigurationRobot.hpp"
#include "MOT_MoteurManager.hpp"
#include "COD_SerialCodeurManager.hpp"

int remote (MOT::CMoteurManager *p_moteurManager);
int askedSpeed(int c, int w);
bool askedMove(int c, int vitesse, MOT::CMoteurManager *p_moteurManager);
void printCommands();

using namespace std;

int main(int argc, char** argv) {

	// Lecture de la configuration
	cout << "Lecture de la Configuration du robot" << endl;

	COF::CConfigurationRobot csvConfigurationRobot = COF::CConfigurationRobot("CofRobotGlouton.csv");
	COF::SConfigRobot configRobot = csvConfigurationRobot.getConfRobot();

	cout << "PA = " <<  setprecision(15) << configRobot.pidKpA << endl;
	cout << "IA = " <<  setprecision(15) << configRobot.pidKiA << endl;
	cout << "DA = " <<  setprecision(15) << configRobot.pidKdA << endl;

	cout << "PD = " <<  setprecision(15) << configRobot.pidKpD << endl;
	cout << "ID = " <<  setprecision(15) << configRobot.pidKiD << endl;
	cout << "DD = " <<  setprecision(15) << configRobot.pidKdD << endl;

	cout << "PP = " <<  setprecision(15) << configRobot.pidKpP << endl;
	cout << "IP = " <<  setprecision(15) << configRobot.pidKiP << endl;
	cout << "DP = " <<  setprecision(15) << configRobot.pidKdP << endl;


	cout << "coeffLongueurRoueGauche = " <<  setprecision(15) << configRobot.coeffLongueurRoueGauche << endl;
	cout << "coeffLongueurRoueDroite = " <<  setprecision(15) << configRobot.coeffLongueurRoueDroite << endl;

	cout << "coeffAngleRoueGauche = " <<  setprecision(15) << configRobot.coeffAngleRoueGauche << endl;
	cout << "coeffAngleRoueDroite = " <<  setprecision(15) << configRobot.coeffAngleRoueDroite << endl;

	cout << "moteursI2cAddr = " <<  configRobot.moteursI2cAddr << endl;

	cout << "codeurSerieTty = " <<  configRobot.codeurSerieTty << endl;
	cout << "servoSerieTty = " <<  configRobot.servoSerieTty << endl;

	cout << "Fin de la lecture de la configuration du robot" << endl;

	// Construction du manageur moteur
	MOT::CMoteurManager moteurManager = MOT::CMoteurManager(configRobot.moteursI2cAddr);

	// Construction du manager des codeurs et de la communication serie
	COD::CSerialCodeurManager codeurManager = COD::CSerialCodeurManager(configRobot.servoSerieTty);

	cout << "argv " << argv[1] << endl;

	if(strcmp(argv[1],"-remote") == 0)
	{
		remote(&moteurManager);
	}
	else
	{

	}

	return 0;
}



int remote (MOT::CMoteurManager *p_moteurManager)
{
	int w = 0;
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

		if(askedMove(cmd, vitesse, p_moteurManager))
			lastMove = cmd;
		else if((tmp = askedSpeed(cmd, w)) != -1)
		{
			vitesse = tmp;
			askedMove(lastMove, vitesse, p_moteurManager);
		}


		p_moteurManager->dummy = true;

		p_moteurManager->dummy = false;


		system ("/bin/stty raw");

	}
	system ("/bin/stty cooked");


	sleep(1);
	p_moteurManager->stop();
	p_moteurManager->apply();


	return 0;
}

void  StopSignalBrutal(int sig, MOT::CMoteurManager *p_moteurManager)
{
	printf("Forcing stop\n");
	p_moteurManager->stop();
	p_moteurManager->apply();
	exit(0);
}


bool askedMove(int c, int vitesse, MOT::CMoteurManager *p_moteurManager)
{

	bool ServoUtiliser = false;

	switch(c)
	{
		case 'z': //haut
			p_moteurManager->gauchePWM(0, vitesse);
			p_moteurManager->droitePWM(0, vitesse);
		break;
		case 's': //bas
			p_moteurManager->gauchePWM(vitesse, 0);
			p_moteurManager->droitePWM(vitesse, 0);
		break;
		case 'q'://gauche
			p_moteurManager->gauchePWM(vitesse, 0);
			p_moteurManager->droitePWM(0, vitesse);
		break;
		case 'd': //droite
			p_moteurManager->gauchePWM(0, vitesse);
			p_moteurManager->droitePWM(vitesse, 0);
		break;
		case 'a': //stop
			p_moteurManager->gauchePWM(0, 0);
			p_moteurManager->droitePWM(0, 0);
		break;
		case 'b': //stop
			p_moteurManager->gauchePWM(vitesse, 0);
			p_moteurManager->droitePWM(0, 0);
		break;
		case 'n': //stop
			p_moteurManager->gauchePWM(0, 0);
			p_moteurManager->droitePWM(vitesse, 0);
		break;
		case 'i': //servoAction

		break;

		default:
			return false;
	}
	if(ServoUtiliser == false)
		p_moteurManager->apply();

	return true;
}


void printCommands()
{
	printf("\n");
	printf("Z Q S D : déplacement\n");
	printf("A : Arrêt du robot\n");
	printf("E : Récupérer les valeurs des codeurs (fausse la génération de points !)\n");
	printf("0-9-* : Réglage de la vitesse du robot de 0 à 100\n");
	printf("R : Ajoute un point de rotation\n");
	printf("F : Ajoute un point de déplacement\n");
	printf("G : Supprime le dernier point de la liste\n");
	printf("T : Affiche la liste des points\n");
	printf(" . puis CTRL-C : Quitter\n");
}

int askedSpeed(int c, int w)
{
	switch(c)
	{
		case '+':
			printf("Vitesse argmente : %i\n", w+5);
			return w = w+5;
		case '-':
			printf("Vitesse diminue : %i\n",w-5);
			return w = w-5;
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
