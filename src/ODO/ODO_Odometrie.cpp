/*
 * ODO_Odometrie.cpp
 *
 *  Created on: 17 nov. 2020
 *      Author: thomas
 */

#include "ODO_Odometrie.hpp"

ODO::COdometrie::COdometrie(COF::SStrategieDeplacement* p_strategieDeplacement)
{
	m_odometrieStruct = {0};
	m_strategieDepalcement = p_strategieDeplacement;

	if (m_strategieDepalcement == NULL) {
		printf("Pointeur NULL !!!!!");
		exit(1);
	}
}

ODO::COdometrie::~COdometrie()
{

}

void ODO::COdometrie::initialiser()
{

}



