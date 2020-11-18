/*
 * ODO_Odometrie.cpp
 *
 *  Created on: 17 nov. 2020
 *      Author: thomas
 */

#include "ODO_Odometrie.hpp"

ODO::COdometrie::COdometrie(COF::SStrategieDeplacement* p_strategieDeplacement, COD::CSerialCodeurManager* p_codeursManager)
{
	m_odometrieStruct = {0};
	m_strategieDepalcement = p_strategieDeplacement;
	m_codeursManager = p_codeursManager;

	if (m_strategieDepalcement == NULL || m_codeursManager == NULL) {
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



