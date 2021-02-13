/*
 * ASV_Asserv.hpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#ifndef _ASV_ASSERV_HPP_
#define _ASV_ASSERV_HPP_


#include "ODO_Odometrie.hpp"
#include "MOT_MoteurPWM.hpp"

namespace ASV
{
	struct SPid
	{
		float erreurOrientationKp;
		float erreurOrientationPrecedente;
		float deltaErreurOrientationKd;
		float sommeErreurOrientationKi;

		float orientationPid;

		float erreurDistanceKp;
		float erreurDistancePrecedente;
		float deltaErreurDistanceKd;
		float sommeErreurDistanceKi;

		float distancePid;
	};

	struct SCmdMoteur
	{
		int cmdMoteurDroit;
		int cmdMoteurGauche;
	};

	class CAsserv
	{
		public:

			CAsserv(MOT::CMoteurPWM* p_moteurManager, ODO::COdometrie* p_odometrie);

			virtual ~CAsserv();

			bool asservirVersCible(COF::SStrategieDeplacement* p_pointStrategieDeplacement);
			void debug();

		private:

			void calculCmdMoteur();
			void appliquerCmdMoteur();
			void verifOverflowCommandes();

			SPid m_structPid;
			SCmdMoteur m_cmdMoteur;
			COF::SConfigRobot* m_configStruct;
			ODO::COdometrie* m_odometrie;
			MOT::CMoteurPWM* m_moteurManager;
	};
}



#endif /* _ASV_ASSERV_HPP_ */
