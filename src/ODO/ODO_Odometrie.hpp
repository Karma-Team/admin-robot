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

namespace COD { class CSerialCodeurManager; class CSPICodeurManager; class CThreadCodeurManager;};

#ifndef _ODO_ODOMETRIE_HPP_
#define _ODO_ODOMETRIE_HPP_


namespace ODO
{
	struct SOdometrieVariables
	{
		int xInit;
		int yInit;
		int angleInit;
		int xDepart;
		int yDepart;
		int xArrive;
		int yArrive;
		int xActuel;
		int yActuel;
		int xDelta;
		int yDelta;
		int angleConsigne;
		int angleActuel;
		int vitesse;
		int nbTickDroit;
		int nbTickGauche;
		int orientationActuel;
		int orientationConsigne;
		int orientationDerive;
		int orientationMoyenne;
		int orientationVersCible;
		int distanceParcourue;
		int distancePrecedent;
		int distanceConsigne;
	};

	class COdometrie
	{
		public:

			COdometrie(COF::SStrategieDeplacement* p_strategieDeplacement, COD::CThreadCodeurManager* p_codeursManager);

			virtual ~COdometrie();

			SOdometrieVariables* getOdometrieVariables();
		
			void setStrategieDeplacement(COF::SStrategieDeplacement* p_strategieDepalcement);

			void initialiser();
			void miseAJourPosition();
			void calculConsigneDeplacement();
			void debug();

		private:
			
			void reorientation();
			void calculConsigne();
			void asservirVersCible();
			
			int m_index;
			int m_cmdMoteurDroit;
			int m_cmdMoteurGauche;
			COF::SStrategieDeplacement* m_strategieDepalcement;
			COF::SConfigRobot* m_configStruct;
			COD::CThreadCodeurManager* m_codeursManager;
			ODO::SOdometrieVariables m_odometrieStruct;

	};
}

#endif /* _ODO_ODOMETRIE_HPP_ */
