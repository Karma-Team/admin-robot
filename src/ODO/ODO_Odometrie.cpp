/*
 * ODO_Odometrie.cpp
 *
 *  Created on: 17 nov. 2020
 *      Author: thomas
 */

#include "ODO_Odometrie.hpp"

ODO::COdometrie::COdometrie(COF::CStrategieDeplacement* p_strategieDeplacement, COD::CSerialCodeurManager* p_codeursManager)
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
	m_odometrieStruct->xDepart = m_strategieDepalcement->getStrategieDeplacement(0)->x;
	m_odometrieStruct->yDepart = m_strategieDepalcement->getStrategieDeplacement(0)->y;
	m_odometrieStruct->yDepart = m_strategieDepalcement->getStrategieDeplacement(0)->y;
	m_odometrieStruct->angleConsigne = m_strategieDepalcement->getStrategieDeplacement(0)->angle;
}

void ODO::COdometrie::reorientation()
{
	if (abs(m_odometrieStruct->angleConsigne - m_odometrieStruct->angleActuel) > 180) {
		if (m_odometrieStruct->angleActuel > 0) {
			m_odometrieStruct->angleActuel -= 360;
		}
		else if (orientation < 0) {
			m_odometrieStruct->angleActuel += 360;
		}
	}
}



