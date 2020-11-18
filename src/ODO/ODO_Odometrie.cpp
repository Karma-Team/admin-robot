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
	m_odometrieStruct.xDepart = m_strategieDepalcement->getStrategieDeplacement(0)->x;
	m_odometrieStruct.yDepart = m_strategieDepalcement->getStrategieDeplacement(0)->y;
	m_odometrieStruct.angleConsigne = m_strategieDepalcement->getStrategieDeplacement(0)->angle;
	m_odometrieStruct.vitesse = 0;
}

void ODO::COdometrie::reorientation()
{
	if (abs(m_odometrieStruct.angleConsigne - m_odometrieStruct.angleActuel) > 180) {
		if (m_odometrieStruct.angleActuel > 0) {
			m_odometrieStruct.angleActuel -= 360;
		}
		else if (m_odometrieStruct.angleActuel < 0) {
			m_odometrieStruct.angleActuel += 360;
		}
	}
}

void ODO::COdometrie::calculConsigne()
{
       /* Pour savoir si la cible est à gauche ou à droite du robot, on
	* calcule le sinus de l'angle entre la cible et le robot
	* sin = Opp/Hyp, on a opp et on retrouve hyp grâce à Pythagore
	* Sinus auxiliaire pour savoir où se trouve la cible par
	* rapport au robot
	*/
	float sinAux = (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart) / (sqrt((m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) * (m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) + (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart) * (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart)));
	float aco = acos((m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) / ((sqrt((m_odometrieStruct.xArrive - m_odometrieStruct.xDepart)*(m_odometrieStruct.xArrive - m_odometrieStruct.xDepart) + (m_odometrieStruct.yArrive - m_odometrieStruct.yDepart)*(m_odometrieStruct.yArrive - m_odometrieStruct.yDepart))))) * 360 /(2 * M_PI);

	// On change la consigne selon le fait que la cible soit à gauche
	// (-aco) ou a droite (+aco) du robot
	m_odometrieStruct.angleConsigne = sinAux > 0 ? -aco : +aco;
    reorientation();
}

void ODO::COdometrie::miseAJourPosition()
{

}



