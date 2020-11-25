#include "COF_ConfigurationRobot.hpp"
#include "MOT_MoteurManager.hpp"
#include "COF_Strategie.hpp"
#include "ODO_Odometrie.hpp"

namespace COD { class CSerialCodeurManager; class CSPICodeurManager;};

#ifndef _REMOTE_
#define _REMOTE_

namespace STR
{
	class CRemote
	{
		public:

			CRemote(MOT::CMoteurManager *p_moteurManager, COD::CSPICodeurManager* p_codeursManager, COF::SConfigRobot* p_configStruct);

			virtual ~CRemote();

			int startRemote();

		private:
			void printCommands();

			int askedSpeed(int p_cmd);

			bool askedMove(int p_cmd, int p_vitesse);

			void printValeurCodeur();

			void asservTest();

			int m_vitesse;
			MOT::CMoteurManager *m_moteurManager;
			COD::CSPICodeurManager* m_codeursManager;
			COF::SConfigRobot* m_configStruct;
	};
}

#endif


