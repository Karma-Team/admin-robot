#include "Fichier.h"
#include <iostream>
#include <string>

using namespace std;

/*vector<Point> Fichier::writePoints(string filename){
	vector<Point> pts;
	string tmpString;
	int abscisse;
	int ordonnee;
	int distanceArret;
	double coefficient;
	int sensR;
	double vitesseRobot;
	double accStart;
	int att;
	int action;
	int blocage;
    int millis;
	ifstream file(filename);

	bool bloc_com = false;
	
	while(file.good()){
		getline(file, tmpString);
		stringstream write(tmpString);
		Point pm(abscisse,ordonnee,distanceArret,coefficient,sensR,vitesseRobot,accStart,att,action, blocage, millis);
		pm.display();
		pts.push_back(pm);
		
		
	}
}*/

vector<Point> Fichier::readPoints(string filename){
	vector<Point> pts;
	string tmpString;
	int abscisse;
	int ordonnee;
	int distanceArret;
	double coefficient;
	int sensR;
	double vitesseRobot;
	double accStart;
	int att;
	int action;
	int blocage;
    int millis;
    int tempsatt;
	string fileaction;
	//char cfileaction;
	ifstream file(filename);

	bool bloc_com = false;

	while(file.good()){
		getline(file, tmpString);
		stringstream read(tmpString);

		if(tmpString.find("/*") != string::npos)
		{
			bloc_com = true;
			cout << "Bloc commentaire: " << tmpString << "\n";
			continue;
		}
		else if(tmpString.find("*/") != string::npos && bloc_com)
		{
			bloc_com = false;
			cout << "Bloc commentaire: " << tmpString << "\n";
			continue;
		}
		else if(bloc_com)
		{
			cout << "Bloc commentaire: " << tmpString << "\n";
			continue;
		}
		else if(countSubstring(tmpString, " ") < 7)
		{
			cout << "Ligne invalide: " << tmpString << "\n";
			continue;
		}
		else if(tmpString.find("#") != string::npos
			|| tmpString.find("//") != string::npos
			|| tmpString.find("--") != string::npos
			|| tmpString.find("%") != string::npos)
		{
			cout << "Commentaire isolé: " << tmpString << "\n";
			continue;
		}

		cout << "Point: " << tmpString << "\n";

		read >> abscisse;
		read >> ordonnee;
		read >> distanceArret;
		read >> coefficient;
		read >> sensR;
		read >> vitesseRobot;
		read >> accStart;
		read >> att;
		read >> action;
		read >> blocage;
        read >> millis;
      	read >> tempsatt;
        read >> fileaction;
		Point p(abscisse,ordonnee,distanceArret,coefficient,sensR,vitesseRobot,accStart,att,action, blocage, millis, tempsatt, fileaction);
		pts.push_back(p);
		fileaction = " ";
	}
	return pts;
}

int Fichier::countSubstring(const std::string& str, const std::string& sub)
{
	if (sub.length() == 0) return 0;
	int count = 0;
	for (size_t offset = str.find(sub); offset != std::string::npos;
	offset = str.find(sub, offset + sub.length()))
	{
		++count;
	}
	return count;
}
