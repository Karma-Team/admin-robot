/*
 * ODO_Odometrie.hpp
 *
 *  Created on: 17 nov. 2020
 *      Author: thomas
 */
#include "COF_Strategie.hpp"
#include "COF_ConfigurationRobot.hpp"
#include <iostream>
#include <math.h>

namespace COD {class CSerialCodeurManager;};

#ifndef _ODO_ODOMETRIE_HPP_
#define _ODO_ODOMETRIE_HPP_


namespace ODO
{
	struct SOdometrieVariables
	{
		int xDepart;
		int yDepart;
		int xArrive;
		int yArrive;
		int xActuel;
		int yActuel;
		float xDelta;
		float yDelta;
		int angleConsigne;
		int angleActuel;
		int vitesse;
		int nbTickDroit;
		int nbTickGauche;
		float orientationActuel;
		float orientationConsigne;
		float orientationDerive;
		float orientationMoyenne;
		float orientationConsigne;
		float distanceParcourue;
		float distancePrecedent;
		float distanceConsigne;
	};
	
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

	class COdometrie
	{
		public:

			COdometrie(COF::CStrategieDeplacement* p_strategieDeplacement, COF::CConfigurationRobot* p_configStruct,  COD::CSerialCodeurManager* p_codeursManager);

			virtual ~COdometrie();

		private:
			
			void initialiser();
			void reorientation();
			void calculConsigne();
			void miseAJourPosition();
			void calculConsigneDeplacement();
			
			int m_index;
			int m_cmdMoteurDroit;
			int m_cmdMoteurGauche;
			COF::CStrategieDeplacement* m_strategieDepalcement;
			COF::CConfigurationRobot* m_configStruct;
			COD::CSerialCodeurManager* m_codeursManager;
			ODO::SOdometrieVariables m_odometrieStruct;
			ODO::SPid m_structPid;
	};
}

#endif /* _ODO_ODOMETRIE_HPP_ */
