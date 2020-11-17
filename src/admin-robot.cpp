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
#include "STR_Remote.hpp"
#include "STR_Autonome.hpp"

using namespace std;

int main(int argc, char** argv) {

	// Lecture de la configuration
	cout << "Lecture de la Configuration du robot" << endl;

	COF::CConfigurationRobot csvConfigurationRobot = COF::CConfigurationRobot("CofRobotGlouton.csv");
	COF::SConfigRobot configRobot = csvConfigurationRobot.getConfRobot();

	cout << "IpServeurTcp = " <<  setprecision(15) << configRobot.ipTcpServeur << endl;

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

	if(strcmp(argv[1],"-remote") == 0)
	{
		STR::CRemote remoteManager = STR::CRemote(&moteurManager, &codeurManager,&configRobot);
		remoteManager.startRemote();
	}
	else
	{
		STR::CAutonome autonomeManager = STR::CAutonome(&moteurManager,&codeurManager,&configRobot);
		autonomeManager.startAutonome();
	}

	return 0;
}



