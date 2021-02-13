#ifndef _REMOTE_
#define _REMOTE_

#include "COF_ConfigurationRobot.hpp"
#include "COF_Strategie.hpp"
#include "ODO_Odometrie.hpp"
#include "MOT_MoteurPWM.hpp"

namespace COD { class CSerialCodeurManager; class CSPICodeurManager; class CThreadCodeurManager;};

namespace STR
{
	class CRemote
	{
		public:

			CRemote(COD::CThreadCodeurManager* p_codeursManager, MOT::CMoteurPWM* p_moteurManager);

			virtual ~CRemote();

			int startRemote();

		private:

			void printCommands();

			int askedSpeed(int p_cmd);

			bool askedMove(int p_cmd, int p_vitesse);

			void printValeurCodeur();

			void asservTest();

			void testCodeurValue();

			int m_vitesse;

			COD::CThreadCodeurManager* m_codeursManager;

			MOT::CMoteurPWM* m_moteurManager;
		
			ODO::COdometrie m_odometrie;
	};
}

#endif


