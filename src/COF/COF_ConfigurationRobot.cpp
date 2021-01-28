/**
 * COF_ConfigurationRobot.cpp
 * @brief permet de charger la configuration du robot au demarrage
 */

#include "COF_ConfigurationRobot.hpp"
#include <csv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

COF::CConfigurationRobot* COF::CConfigurationRobot::inst()
{
  static CConfigurationRobot m_singleton;

  return(&m_singleton);
}

COF::CConfigurationRobot::CConfigurationRobot()
{

}


void COF::CConfigurationRobot::readCsv(char * p_csvConfigFile)
{
	char* type;


	io::CSVReader<2> in(p_csvConfigFile);

	char* ip;

	in.read_row(type, ip);
	snprintf(m_configRobotStruc.ipTcpServeur, sizeof(m_configRobotStruc.ipTcpServeur), "%s", ip);

	double value;

	in.read_row(type, value);
	m_configRobotStruc.pidKpA = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKiA = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKdA = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKpD = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKiD = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKdD = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKpP = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKiP = value;

	in.read_row(type, value);
	m_configRobotStruc.pidKdP = value;

	in.read_row(type, value);
	m_configRobotStruc.coeffLongueurRoueGauche = value;

	in.read_row(type, value);
	m_configRobotStruc.coeffLongueurRoueDroite = value;

	in.read_row(type, value);
	m_configRobotStruc.coeffAngleRoueGauche = value;

	in.read_row(type, value);
	m_configRobotStruc.coeffAngleRoueDroite = value;

	int addr = 0;
	in.read_row(type, addr);
	m_configRobotStruc.moteursI2cAddr = addr;

	char *device;
	in.read_row(type, device);
	snprintf(m_configRobotStruc.codeurSerieTty, sizeof(m_configRobotStruc.codeurSerieTty), "%s", device);


	in.read_row(type, device);
	snprintf(m_configRobotStruc.servoSerieTty, sizeof(m_configRobotStruc.servoSerieTty), "%s", device);

}

COF::SConfigRobot* COF::CConfigurationRobot::getConfRobot()
{
	return &m_configRobotStruc;
}




