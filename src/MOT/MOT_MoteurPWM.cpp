#include "MOT_MoteurPWM.hpp"
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

using namespace std;

MOT::CMoteurPWM::CMoteurPWM()
{
	init();
}

MOT::CMoteurPWM::~CMoteurPWM()
{
  //rien a faire
}

void MOT::CMoteurPWM::init()
{
	pinMode(SensRotationADroiteIn1, OUTPUT);
	pinMode(SensRotationBDroiteIn2, OUTPUT);

	pinMode(SensRotationAGaucheIn3, OUTPUT);
	pinMode(SensRotationBGaucheIn4, OUTPUT);

	digitalWrite(SensRotationADroiteIn1, LOW);
	digitalWrite(SensRotationBDroiteIn2, LOW);
	digitalWrite(SensRotationAGaucheIn3, LOW);
	digitalWrite(SensRotationBGaucheIn4, LOW);

	/*pinMode(PwmMoteurDroite, PWM_OUTPUT);
	pinMode(PwmMoteurGauche, PWM_OUTPUT);*/

	if (softPwmCreate(PwmMoteurDroite, 0, 100) != 0)
	{
		printf("Erreur initialisation pwm moteur droitAV");
		exit(1);
	}

	if (softPwmCreate(PwmMoteurGauche, 0, 100) != 0)
	{
		printf("Erreur initialisation pwm moteur gaucheAV");
		exit(1);
	}
}

void MOT::CMoteurPWM::setMoteurSpeedDroite(int p_inAv, int p_inArr)
{
	if(p_inAv > 0 && p_inArr == 0)
	{
		digitalWrite(SensRotationADroiteIn1, HIGH);
		digitalWrite(SensRotationBDroiteIn2, LOW);
		softPwmWrite(PwmMoteurDroite, p_inAv);
		//pwmWrite(PwmMoteurDroite,1024);
	}
	else if(p_inAv == 0 && p_inArr > 0)
	{
		digitalWrite(SensRotationADroiteIn1, LOW);
		digitalWrite(SensRotationBDroiteIn2, HIGH);
		softPwmWrite(PwmMoteurDroite, p_inArr);
		//pwmWrite(PwmMoteurDroite, 1024);
	}
	else
	{
		digitalWrite(SensRotationADroiteIn1, HIGH);
		digitalWrite(SensRotationBDroiteIn2, HIGH);
		softPwmWrite(PwmMoteurDroite, 0);
	}
}

void MOT::CMoteurPWM::setMoteurSpeedGauche(int p_inAv, int p_inArr)
{
	if(p_inAv > 0 && p_inArr == 0)
	{
		digitalWrite(SensRotationAGaucheIn3, HIGH);
		digitalWrite(SensRotationBGaucheIn4, LOW);
		softPwmWrite(PwmMoteurGauche, p_inAv);
		//pwmWrite(PwmMoteurGauche, 1024);
	}
	else if(p_inAv == 0 && p_inArr > 0)
	{
		digitalWrite(SensRotationAGaucheIn3, LOW);
		digitalWrite(SensRotationBGaucheIn4, HIGH);
		softPwmWrite(PwmMoteurGauche, p_inArr);
		//pwmWrite(PwmMoteurGauche, 1024);
	}
	else
	{
		digitalWrite(SensRotationAGaucheIn3, HIGH);
		digitalWrite(SensRotationBGaucheIn4, HIGH);
		softPwmWrite(PwmMoteurGauche, 0);
	}
}
  
bool MOT::CMoteurPWM::isBetween(int p_min, int p_val, int p_max)
 {
        if(p_val < p_min || p_val > p_max)
                return false;
        return true;
 }

void MOT::CMoteurPWM::setMoteurSpeed(int p_dArr, int p_dAvt, int p_gArr, int p_gAvt)
{
  if((isBetween(0, p_dArr, 100) == true) && (isBetween(0, p_dAvt, 100) == true))
  {
    setMoteurSpeedDroite(p_dAvt,p_dArr);
  }
  else
  {
    setMoteurSpeedDroite(0,0);
  }
  
  if((isBetween(0, p_gArr, 100) == true) && (isBetween(0, p_gAvt, 100) == true))
  {
    setMoteurSpeedGauche(p_gAvt,p_gArr);
  }
  else
  {
    setMoteurSpeedGauche(0,0);
  }

  //debug();
}

void MOT::CMoteurPWM::debug()
{
	cout << " SensRotationADroiteIn1 " << digitalRead(SensRotationADroiteIn1) << endl;
	cout << " SensRotationBDroiteIn2 " << digitalRead(SensRotationBDroiteIn2) << endl;
	cout << " PwmMoteurDroite " << analogRead(PwmMoteurDroite) << endl;
	cout << " SensRotationAGaucheIn3 " << digitalRead(SensRotationAGaucheIn3) << endl;
	cout << " SensRotationBGaucheIn4 " << digitalRead(SensRotationBGaucheIn4) << endl;
	cout << " PwmMoteurGauche " << analogRead(PwmMoteurGauche) << endl;
}


