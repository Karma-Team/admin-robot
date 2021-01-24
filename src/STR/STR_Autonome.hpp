#include "COF_ConfigurationRobot.hpp"
#include "TCP/TCP_Client.hpp"
#include "TCP/TCP_Server.hpp"
#include "MOT_MoteurPWM.hpp"

namespace COD { class CSerialCodeurManager; class CSPICodeurManager; class CThreadCodeurManager;};


#ifndef _AUTONOME_
#define _AUTONOME_

namespace STR
{

	class CAutonome
	{
		public:

			CAutonome(COD::CThreadCodeurManager* p_codeursManager, MOT::CMoteurPWM* p_moteurManager);

			virtual ~CAutonome();

			void startAutonome();

		private:

			static void asserv(bool* p_aliveAsservThread, COD::CThreadCodeurManager* p_codeursManager);

			static void tcpClient(bool* p_aliveTcpClientThread, TCP::CTcpClient* p_tcpClient, SPathMsg* p_pathMsgPath);

			COD::CThreadCodeurManager* m_codeursManager;
			COF::SConfigRobot* m_configStruct;

			TCP::CTcpClient m_tcpClient;

			bool m_aliveAsservThread;
			bool m_aliveTcpClientThread;

			string m_ipServeur;

			SPathMsg m_pathMsgPath = {.hd={MSG_ID_PATH, 			sizeof(SPathMsg)}};

	};
}

#endif

