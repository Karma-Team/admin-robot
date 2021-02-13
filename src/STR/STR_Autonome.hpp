#ifndef _AUTONOME_
#define _AUTONOME_

#include "COF_ConfigurationRobot.hpp"
#include "TCP/TCP_Client.hpp"
#include "TCP/TCP_Server.hpp"
#include "MOT_MoteurPWM.hpp"
#include <string.h>

namespace COD { class CSerialCodeurManager; class CSPICodeurManager; class CThreadCodeurManager;};


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

			static void tcpClient(bool* p_aliveTcpClientThread, TCP::CTcpClient* p_tcpClient, SMsgOrderPathBody* p_pathMsgPath);

			bool m_aliveAsservThread;
			bool m_aliveTcpClientThread;

			std::string m_ipServeur;


	};
}

#endif

