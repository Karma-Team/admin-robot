#include "Point.h"

#include <iostream>
#include <string>

using namespace std;


Point::Point(int x, int y, int distance, double Coeff, int sens, double vitesse,double acc, int attente, int actionp, int blocagep, int millis, int tatt, string fa)
{
	abscisse = x;
	ordonnee = y;
	distanceArret = distance;
	coefficient = Coeff;
	sensR = sens;
	vitesseRobot = vitesse;
	accStart=acc;
	att=attente;
	action=actionp;
	blocage = blocagep;
    timeout = millis;
    timeatt = tatt;
    fileaction = fa;
	
}

void Point::display()
{
	cout << abscisse << ' ' << ordonnee << ' ' << distanceArret << ' ' <<
		coefficient << ' ' << sensR << ' ' << vitesseRobot << ' '
		<< accStart << ' ' << att << ' ' << action << ' ' << blocage << ' ' << timeout << ' ' << timeatt << ' ' << fileaction << endl;
}

int Point::getRecalage()
{
	return timeatt;
} 

void Point::setRecalage(int tempatt_)
{
	timeatt = tempatt_;
}

string Point::getFServo()
{
	return fileaction;
}

void Point::setFServo(string Fservo)
{
	fileaction = Fservo;
}



int Point::getX()
{
	return abscisse;
}

void Point::setX(int x)
{
	abscisse = x;
}


int Point::getY()
{
	return ordonnee;
}

void Point::setY(int y)
{
	ordonnee=y;
}

int Point::getDist()
{
	return distanceArret;
}

void Point::setDist(int dist)
{
	distanceArret=dist;
}

double Point::getCoeff()
{
	return coefficient;
}

void Point::setCoeff(double coeff)
{
	coefficient = coeff;
}

int Point::getSens()
{
	return sensR;
}

void Point::setSens(int sens)
{
	sensR=sens;
}

double Point::getVitesse()
{
	return vitesseRobot;
}

void Point::setVitesse(double vitesse)
{
	vitesseRobot=vitesse;
}

double Point::getAcc()
{
	return accStart;
}

void Point::setAcc(double acc)
{
	accStart=acc;
}

int Point::getAttente()
{
	return att;
}

void Point::setAttente(int attente)
{
	att=attente;
}

int Point::getAction()
{
	return action;
}

void Point::setAction(int actionp)
{
	action=actionp;
}

void Point::setBlocage(int blocagep)
{
	blocage = blocagep;
}

int Point::getBlocage()
{
	return blocage;
}

int Point::getTimeout(){
    return timeout;
}

void Point::setTimeout(int millis){
    timeout = millis;
}

