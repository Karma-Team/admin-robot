/*
 * ATL_CsvAtelierDecode.cpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ATL_CsvAtelierDecode.hpp"
#include "COF_ConfigurationRobot.hpp"

#include <csv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <thread>


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

	io::CSVReader<9> in(p_csvAtelierFile);

	while(in.read_row(m_scsvAtelierAction.id, m_scsvAtelierAction.modeServo, m_scsvAtelierAction.vitesseAngleServo, m_scsvAtelierAction.timeoutServo, m_scsvAtelierAction.vitesseDeplacement,m_scsvAtelierAction.angleDeplacement, m_scsvAtelierAction.xDeplacement, m_scsvAtelierAction.yDeplacement, m_scsvAtelierAction.timeoutAtelier))
	{
		uint32_t timeout = 0;
		std::thread threadSeralServoAtelier (threadActionneurAtelier,&serialServoApi, &m_scsvAtelierAction.modeServo, &m_scsvAtelierAction.id, &m_scsvAtelierAction.vitesseAngleServo, &m_scsvAtelierAction.timeoutServo);
		threadSeralServoAtelier.join();
		
		while(timeout < m_scsvAtelierAction.timeoutAtelier )
		{
			timeout++;
			usleep(1 * 1000);
		}
	}
}



void ATL::CCsvAtelierDecode::threadActionneurAtelier(SSV::CSerialServoApi* p_serialServoApi, char* p_modeServo, uint32_t* p_id, double* p_vitesseAngleServo, uint32_t* p_timeoutServo)
{
	switch (*p_modeServo)
	{
		case 'a':
		{
			(void)p_serialServoApi->activerServoAngle(*p_id, *p_vitesseAngleServo, *p_timeoutServo);
		}
		break;

		case 'm':
		{
			(void)p_serialServoApi->activerServoMoteur(*p_id, *p_vitesseAngleServo, *p_timeoutServo);
		}
		break;

		default:
		{
			// rien a faire
		}
		break;
	}
}
