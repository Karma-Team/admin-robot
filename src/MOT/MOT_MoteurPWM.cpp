#include "MOT_MoteurPWM.hpp"
#include <wiringPi.h>
#include <softPwm.h>


MOT::CMoteurPWM* MOT::CMoteurPWM::inst()
{
  static CMoteurPWM m_singleton;
  
  return(m_singleton);
}

MOT::CMoteurPWM::CMoteurPWM()
{
  //rien a faire
}

void MOT::CMoteurPWM::init()
{
  if(softPwmCreate (MDinAV, 0, 100) != 0)
  {
    printf("Erreur initialisation pwm moteur droitAV");
    exit(1);
  }
  
  if(softPwmCreate (MGinAV, 0, 100) != 0)
  {
    printf("Erreur initialisation pwm moteur gaucheAV");
    exit(1);
  }
  
    if(softPwmCreate (MDinARR, 0, 100) != 0)
  {
    printf("Erreur initialisation pwm moteur droitARR");
    exit(1);
  }
  
  if(softPwmCreate (MGinARR, 0, 100) != 0)
  {
    printf("Erreur initialisation pwm moteur gaucheARR");
    exit(1);
  }
}

void MOT::CMoteurPWM::setMoteurSpeedDroite(int p_inAv, int p_inArr)
{
  softPwmWrite(MDinAV, p_inAv);
  softPwmWrite(MDinARR, p_inArr);
}

void MOT::CMoteurPWM::setMoteurSpeedGauche(int p_inAv, int p_inArr)
{
  softPwmWrite(MGinAV, p_inAv);
  softPwmWrite(MGinARR, p_inArr);
}
  
bool MOT::CMoteurPWM::isBetween(int p_min, int p_val, int p_max)
 {
        if(val < min || val > max)
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
}
