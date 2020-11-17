/**
 * COF_Strategie.cpp
 * @brief permet de charger la strategie
 */

#include "COF_Strategie.hpp"
#include <csv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;


COF::CStrategieDeplacement::CStrategieDeplacement(char * p_csvStrategieDeplacementFile)
{
	snprintf(m_csvStrategieDeplacementFile, sizeof(p_csvStrategieDeplacementFile), "%s", p_csvStrategieDeplacementFile);
	CStrategieDeplacement::readCsv();
}

void COF::CStrategieDeplacement::readCsv()
{
	int x = 0;
	int y = 0;
	int angle = 0;
	int vitesse = 0;
	char* actions;
	int index = 0;

	io::CSVReader<5> in(m_csvStrategieDeplacementFile);
	in.read_row(x, y, angle, vitesse, actions);

	while(in.read_row(x, y, angle, vitesse, actions))
	{
		m_strategieDeplacementStruct[index].x = x;
		m_strategieDeplacementStruct[index].y = y;
		m_strategieDeplacementStruct[index].angle = angle;
		m_strategieDeplacementStruct[index].vitesse = vitesse;
		snprintf(m_strategieDeplacementStruct[index].actions, sizeof(m_strategieDeplacementStruct[index].actions), "%s", actions);
		index++;
	}

}

COF::SStrategieDeplacement* COF::CStrategieDeplacement::getStrategieDeplacement(int p_index)
{
	return &m_strategieDeplacementStruct[p_index];
}

