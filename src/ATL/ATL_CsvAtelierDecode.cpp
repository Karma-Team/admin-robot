/*
 * ATL_CsvAtelierDecode.cpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ATL_CsvAtelierDecode.hpp"
#include "COF_ConfigurationRobot.hpp"
#include "SSV_SerialServoApi.hpp"

#include <csv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>


using namespace std;

/*ATL::CCsvAtelierDecode::CCsvAtelierDecode(char * p_csvAtelierFile)
{
	snprintf(m_csvAtelierDecodeFile, sizeof(m_csvAtelierDecodeFile), "%s", p_csvAtelierFile);
	m_index = 0;
	CCsvAtelierDecode::readCsv();
}

ATL::CCsvAtelierDecode::~CCsvAtelierDecode()
{
	// rien a faire
}*/

ATL::CCsvAtelierDecode* ATL::CCsvAtelierDecode::inst()
{
  static CCsvAtelierDecode m_singleton;

  return(&m_singleton);
}

ATL::CCsvAtelierDecode::CCsvAtelierDecode()
{
	m_index = 0;
}

void ATL::CCsvAtelierDecode::readCsv(char * p_csvAtelierFile)
{
	SSV::CSerialServoApi serialServoApi = SSV::CSerialServoApi(COF::CConfigurationRobot::inst()->getConfRobot()->servoSerieTty, 115200);

	io::CSVReader<8> in(p_csvAtelierFile);

	while(in.read_row(m_scsvAtelierAction.id, m_scsvAtelierAction.modeServo, m_scsvAtelierAction.vitesseAngleServo, m_scsvAtelierAction.vitesseDeplacement,m_scsvAtelierAction.angleDeplacement, m_scsvAtelierAction.xDeplacement, m_scsvAtelierAction.yDeplacement, m_scsvAtelierAction.timeout))
	{
		switch (m_scsvAtelierAction.modeServo)
		{
			case 'm':
			{
				(void)serialServoApi.activerServoAngle(m_scsvAtelierAction.id, m_scsvAtelierAction.vitesseAngleServo, m_scsvAtelierAction.timeout);
			}
			break;

			case 'a':
			{
				(void)serialServoApi.activerServoMoteur(m_scsvAtelierAction.id, m_scsvAtelierAction.vitesseAngleServo, m_scsvAtelierAction.timeout);
			}
			break;

			default:
			{
				// rien a faire
			}
			break;
		}
	}

}
