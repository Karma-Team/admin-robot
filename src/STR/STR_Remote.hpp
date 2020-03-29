#include "MOT_MoteurManager.hpp"

#ifndef _REMOTE_
#define _REMOTE_

namespace STR
{
	class CRemote
	{
		public:

			CRemote(MOT::CMoteurManager *p_moteurManager);

			virtual ~CRemote();

			int startRemote();

		private:

			int askedSpeed(int p_cmd);

			bool askedMove(int p_cmd, int p_vitesse);

			void printCommands();

			int m_vitesse;

			MOT::CMoteurManager *m_moteurManager;
	};
}

#endif


