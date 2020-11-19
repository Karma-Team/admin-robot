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
		float consigneOrientation;
		float orientation;
		float orientationDerive;
		float orientationMoyenne;
		float distanceParcourue;
		float distancePrecedent;
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
			
			int m_index;
			COF::CStrategieDeplacement* m_strategieDepalcement;
			COF::CConfigurationRobot* m_configStruct;
			COD::CSerialCodeurManager* m_codeursManager;
			ODO::SOdometrieVariables m_odometrieStruct;
	};
}

#endif /* _ODO_ODOMETRIE_HPP_ */
