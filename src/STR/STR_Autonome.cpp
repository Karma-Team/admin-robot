#include <iostream>
#include <iomanip>      // std::setprecision
#include <wiringPi.h>
#include <string.h>

#include "COD_ThreadCodeurManager.hpp"
#include "COF_Strategie.hpp"
#include "ASV_Asserv.hpp"
#include "MOT_MoteurPWM.hpp"
#include "STR_Autonome.hpp"


STR::CAutonome::CAutonome(COD::CThreadCodeurManager* p_codeursManager, MOT::CMoteurPWM* p_moteurManager)
{

}

STR::CAutonome::~CAutonome()
{
	// rien a faire
}

void STR::CAutonome::startAutonome()
{
	system ("/bin/stty raw");
	int cmd;

	while((cmd=getchar())!= '.')
	{

	}
}

void STR::CAutonome::asserv(bool* p_aliveAsservThread, COD::CThreadCodeurManager* p_codeursManager)
{

}

void STR::CAutonome::tcpClient(bool* p_aliveTcpClientThread, TCP::CTcpClient* p_tcpClient, SMsgOrderPathBody* p_pathMsgPath)
{

}
