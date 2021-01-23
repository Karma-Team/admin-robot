#include <iostream>
#include <iomanip>      // std::setprecision
#include <wiringPi.h>
#include <string.h>

#include "COD_ThreadCodeurManager.hpp"
#include "COF_Strategie.hpp"
#include "ASV_Asserv.hpp"
#include "MOT_MoteurPWM.hpp"
#include "STR_Autonome.hpp"


STR::CAutonome::CAutonome(COD::CThreadCodeurManager* p_codeursManager, MOT::CMoteurPWM* p_moteurManager, COF::SConfigRobot* p_configStruct)
{
	m_aliveAsservThread = false;
	m_aliveTcpClientThread = false;

	m_codeursManager = p_codeursManager;
	m_configStruct = p_configStruct;

	if (p_codeursManager == NULL || m_configStruct == NULL) {
		printf("Pointeur NULL !!!!!");
		exit(1);
	}

	stringstream copyString;
	copyString << m_configStruct->ipTcpServeur;
	copyString >> m_ipServeur;

	m_tcpClient = TCP::CTcpClient(54000, m_ipServeur);

}

STR::CAutonome::~CAutonome()
{
	// rien a faire
}

void STR::CAutonome::startAutonome()
{
	thread threadAsserv(asserv, &m_aliveAsservThread, m_codeursManager, m_configStruct);
	thread threadTcpClient(tcpClient, &m_aliveTcpClientThread, &m_tcpClient, &m_pathMsgPath);

	system ("/bin/stty raw");
	int cmd;

	while((cmd=getchar())!= '.')
	{

	}
}

void STR::CAutonome::asserv(bool* p_aliveAsservThread, COD::CThreadCodeurManager* p_codeursManager, COF::SConfigRobot* p_configStruct)
{
	*p_aliveAsservThread = true;

	while (*p_aliveAsservThread != false)
	{

	}
}

void STR::CAutonome::tcpClient(bool* p_aliveTcpClientThread, TCP::CTcpClient* p_tcpClient, SPathMsg* p_pathMsgPath)
{
	int client;

	client = p_tcpClient->initTcpClient();
	*p_aliveTcpClientThread = true;

	while(*p_aliveTcpClientThread != false)
	{
		p_tcpClient->requestMsgToServer(MSG_ID_PATH, p_pathMsgPath);
	}
}
