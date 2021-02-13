#ifndef _FICHIER_H_
#define _FICHIER_H_

#pragma once
#include "Point.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Fichier{
	public :
	static vector<Point> readPoints(string);
	//static vector<Point> writePoints(string);
	static int countSubstring(const std::string&, const std::string&);
};

#endif
