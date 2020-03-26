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
#include "COF_ConfigurationRobot.hpp"
#include "MOT_MoteurManager.hpp"
#include "COD_SerialCodeurManager.hpp"

using namespace std;

int main() {

	// Lecture de la configuration
	cout << "Lecture de la Configuration du robot" << endl;

	COF::CConfigurationRobot csvConfigurationRobot = COF::CConfigurationRobot("CofRobotGlouton.csv");
	COF::SConfigRobot configRobot = csvConfigurationRobot.getConfRobot();

	cout << "P = " <<  setprecision(15) << configRobot.pidKpA << endl;
	cout << "I = " <<  setprecision(15) << configRobot.pidKiA << endl;
	cout << "D = " <<  setprecision(15) << configRobot.pidKdA << endl;

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

	return 0;
}
