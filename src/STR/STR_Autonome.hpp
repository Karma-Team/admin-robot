#include "COF_ConfigurationRobot.hpp"
#include "COD_SerialCodeurManager.hpp"
#include "TCP/TCP_Client.hpp"
#include "TCP/TCP_Server.hpp"

#ifndef _AUTONOME_
#define _AUTONOME_

namespace STR
{

	class CAutonome
	{
		public:

			CAutonome(COD::CSerialCodeurManager* p_codeursManager, COF::SConfigRobot* p_configStruct);

			virtual ~CAutonome();

			void startAutonome();

		private:

			static void asserv(bool* p_aliveAsservThread, COD::CSerialCodeurManager* p_codeursManager, COF::SConfigRobot* p_configStruct);

			static void tcpClient(bool* p_aliveTcpClientThread, TCP::CTcpClient* p_tcpClient, SPathMsg* p_pathMsgPath);

			COD::CSerialCodeurManager* m_codeursManager;
			COF::SConfigRobot* m_configStruct;

			TCP::CTcpClient m_tcpClient;

			bool m_aliveAsservThread;
			bool m_aliveTcpClientThread;

			string m_ipServeur;

			SPathMsg m_pathMsgPath = {.hd={MSG_ID_PATH, 			sizeof(SPathMsg)}};

	};
}

#endif

