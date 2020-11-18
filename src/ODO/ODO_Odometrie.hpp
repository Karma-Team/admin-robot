/*
 * ODO_Odometrie.hpp
 *
 *  Created on: 17 nov. 2020
 *      Author: thomas
 */
#include "COF_Strategie.hpp"
#include <iostream>

#ifndef _ODO_ODOMETRIE_HPP_
#define _ODO_ODOMETRIE_HPP_


namespace ODO
{
	struct SOdometrieVariables
	{
		int xDepart;
		int yDepart;
		int xConsigne;
		int yConsigne;
		int angleConsigne;
		int angleActuel;
		int vitesse;
		int nbTickDroit;
		int nbTickGauche;
		int consigneOrientation;
		int orientation;
	};

	class COdometrie
	{

		public:

			COdometrie(COF::SStrategieDeplacement* p_strategieDeplacement);

			virtual ~COdometrie();

		private :

			void initialiser();

			COF::SStrategieDeplacement* m_strategieDepalcement;
			ODO::SOdometrieVariables m_odometrieStruct;

	};

}


#endif /* _ODO_ODOMETRIE_HPP_ */
