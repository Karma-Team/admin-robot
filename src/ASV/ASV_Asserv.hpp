/*
 * ASV_Asserv.hpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ODO_Odometrie.hpp"
#include "MOT_MoteurManager.hpp"

#ifndef _ASV_ASSERV_HPP_
#define _ASV_ASSERV_HPP_


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

			CAsserv(MOT::CMoteurManager* p_moteurManager, COF::SConfigRobot* p_configStruct, ODO::COdometrie* p_odometrie);

			virtual ~CAsserv();

			bool asservirVersCible();

		private:

			void calculCmdMoteur();
			void appliquerCmdMoteur();
			void verifOverflowCommandes();

			SPid m_structPid;
			SCmdMoteur m_cmdMoteur;
			MOT::CMoteurManager* m_moteurManager;
			COF::SConfigRobot* m_configStruct;
			ODO::COdometrie* m_odometrie;
	};
}



#endif /* _ASV_ASSERV_HPP_ */
