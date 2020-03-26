#include <string>

using namespace std;

class Point
{
	public :
		Point(int x, int y, int distance, double Coeff, int sens, double vitesse,double acc, int attente, int action, int blocage, int millis, int tatt, string fa);

		int getX();
		void setX(int x);

		int getRecalage();
		void setRecalage(int tempatt_);

		string getFServo();
		void setFServo(string Fservo);
		
		int getY();
		void setY(int y);
		
		int getDist();
		void setDist(int dist);
		
		double getCoeff();
		void setCoeff(double coeff);
		
		int getApince();
		void setApince(int p);

		int getSens();
		void setSens(int sens);

		double getVitesse();
		void setVitesse(double vitesse);

		double getAcc();
		void setAcc(double acc);

		int getAttente();
		void setAttente(int attente);

		int getBlocage();
		void setBlocage(int blocage);

		int getAction();
		void setAction(int action);

		int getTimeout();
		void setTimeout(int millis);

		void display();

	private :
		int abscisse;
		int ordonnee;
		int distanceArret;
		int blocage;
		double coefficient;
		int sensR;
		double vitesseRobot;
		double accStart;
		int att;
		int action;
        int timeout;
        int timeatt;
		string fileaction;
};
