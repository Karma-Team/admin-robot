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

COF::CStrategieDeplacement* COF::CStrategieDeplacement::inst()
{
  static CStrategieDeplacement m_singleton;

  return(&m_singleton);
}

COF::CStrategieDeplacement::CStrategieDeplacement()
{
	m_index = 0;
}
void COF::CStrategieDeplacement::readCsv(char * p_csvStrategieDeplacementFile)
{
	int x = 0;
	int y = 0;
	int angle = 0;
	int vitesse = 0;
	int timeout = 0;
	char* actions;
	int index = 0;

	io::CSVReader<6> in(p_csvStrategieDeplacementFile);
	in.read_header(io::ignore_extra_column, "x", "y", "angle", "vitesse", "timeout","atelier");
	
	while(in.read_row(x, y, angle, vitesse, timeout, actions))
	{
		m_strategieDeplacementStruct[index].x = x;
		m_strategieDeplacementStruct[index].y = y;
		m_strategieDeplacementStruct[index].angle = angle;
		m_strategieDeplacementStruct[index].vitesse = vitesse;
		m_strategieDeplacementStruct[index].timeout = timeout;
		snprintf(m_strategieDeplacementStruct[index].actions, sizeof(m_strategieDeplacementStruct[index].actions), "%s", actions);
		index++;
	}
	m_index = index;

}

COF::SStrategieDeplacement* COF::CStrategieDeplacement::getStrategieDeplacement(int p_index)
{
	return &m_strategieDeplacementStruct[p_index];
}

int COF::CStrategieDeplacement::getSizeStrategie()
{
	return m_index;
}
