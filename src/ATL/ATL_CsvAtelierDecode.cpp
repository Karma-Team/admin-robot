/*
 * ATL_CsvAtelierDecode.cpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ATL_CsvAtelierDecode.hpp"
#include "COF_ConfigurationRobot.hpp"
#include "ASV_Asserv.hpp"

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

void ATL::CCsvAtelierDecode::readCsv(char * p_csvAtelierFile, MOT::CMoteurPWM* p_moteurManager,  ODO::COdometrie* p_odometrie)
{
	if (p_csvAtelierFile == NULL || p_moteurManager == NULL || p_odometrie == NULL)
	{
		printf("ERREUR un des pointeurs fournie est null p_csvAtelierFile %d p_moteurManager %d p_odometrie %d, p_csvAtelierFile, p_odometrie, p_odometrie);
		exit(1);
	}
		       
	SSV::CSerialServoApi serialServoApi = SSV::CSerialServoApi(COF::CConfigurationRobot::inst()->getConfRobot()->servoSerieTty, 115200);

	io::CSVReader<9> in(p_csvAtelierFile);
	in.read_header(io::ignore_extra_column, "idServo", "ModeServo", "Angle/Vitesse", "TimeoutServo", "xDeplacement", "yDeplacement", "AngleDeplacement", "VitesseDeplacement", "timeoutAtelier");
	
	while(in.read_row(m_scsvAtelierAction.id, m_scsvAtelierAction.modeServo, m_scsvAtelierAction.vitesseAngleServo, m_scsvAtelierAction.timeoutServo, m_scsvAtelierAction.xDeplacement, m_scsvAtelierAction.yDeplacement, m_scsvAtelierAction.angleDeplacement, m_scsvAtelierAction.vitesseDeplacement, m_scsvAtelierAction.timeoutAtelier))
	{
		uint32_t timeout = 0;
		std::thread threadSeralServoAtelier (threadActionneurAtelier,&serialServoApi, &m_scsvAtelierAction.modeServo, &m_scsvAtelierAction.id, &m_scsvAtelierAction.vitesseAngleServo, &m_scsvAtelierAction.timeoutServo);
		threadSeralServoAtelier.detach(); // Execution du thread sans bloquer le thread principal
		
		SStrategieDeplacement strategieDeplacementAtelier = {m_scsvAtelierAction.xDeplacement, m_scsvAtelierAction.yDeplacement, m_scsvAtelierAction.angleDeplacement, m_scsvAtelierAction.vitesseDeplacement, "null"};
		std::thread threadAsservDeplacmentAtelier (threadDeplacementAtelier, p_moteurManager, p_odometrie, &strategieDeplacementAtelier);
		threadAsservDeplacmentAtelier.detach(); // Execution du thread sans bloquer le thread principal
		
		while(timeout < m_scsvAtelierAction.timeoutAtelier ) // Attente de la fin de l'action de la ligne de l'atelier pour passer a la suivante
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

void ATL::CCsvAtelierDecode::threadDeplacementAtelier(MOT::CMoteurPWM* p_moteurManager, ODO::COdometrie* p_odometrie, COF::SStrategieDeplacement* p_pointStrategieAtelier)
{
	
}
