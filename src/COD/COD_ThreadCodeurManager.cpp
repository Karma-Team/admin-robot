#include "COD_ThreadCodeurManager.hpp"

#include <cstdint>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <iostream>
#include <thread>

#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>

using namespace std;

volatile int m_TicksCodeurGauche = 0;
volatile int m_TicksCodeurDroit = 0;

COD::CThreadCodeurManager::CThreadCodeurManager()
{


	initialisation();
}

COD::CThreadCodeurManager::~CThreadCodeurManager()
{


}

void COD::CThreadCodeurManager::initialisation()
{
	printf("Initialisation codeur\n");
	pinMode(PIN_GPIO_SA_DROITE,INPUT);
	pinMode(PIN_GPIO_SB_DROITE,INPUT);
	pinMode(PIN_GPIO_SA_GAUCHE,INPUT);
	pinMode(PIN_GPIO_SB_GAUCHE,INPUT);

	m_TicksCodeurGauche = 0;
	m_TicksCodeurDroit = 0;

	if(wiringPiISR(PIN_GPIO_SA_DROITE, INT_EDGE_RISING, &compterTicDroit) < 0 )
	{
	      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
	      exit(1);
	}
	if(wiringPiISR(PIN_GPIO_SB_GAUCHE, INT_EDGE_RISING, &compterTicGauche) < 0 )
	{
	      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
	      exit(1);
	}

}

void COD::CThreadCodeurManager::reset()
{
	m_TicksCodeurGauche = 0;
	m_TicksCodeurDroit = 0;
}

void COD::CThreadCodeurManager::compterTicDroit ()
{
	  if (digitalRead(PIN_GPIO_SB_DROITE) == HIGH)
	  {
		  m_TicksCodeurDroit--;
	  }
	  else
	  {
		  m_TicksCodeurDroit++;
	  }
}

void COD::CThreadCodeurManager::compterTicGauche ()
{
	  if (digitalRead(PIN_GPIO_SB_GAUCHE) == HIGH)
	  {
		  m_TicksCodeurGauche++;
	  }
	  else
	  {
		  m_TicksCodeurGauche--;
	  }
}

int COD::CThreadCodeurManager::getTicksDroit()
{
	return m_TicksCodeurDroit;
}

int COD::CThreadCodeurManager::getTicksGauche()
{
	return m_TicksCodeurGauche;
}

/*void COD::CThreadCodeurManager::compterTicDroit (void* p_Ccodeur)
{
	  COD::CThreadCodeurManager* codeurManager = static_cast<COD::CThreadCodeurManager*>(p_Ccodeur);

	  if (digitalRead(PIN_GPIO_SB_DROITE) == HIGH)
	  {
		  codeurManager->m_TicksCodeurDroit--;
	  }
	  else
	  {
		  codeurManager->m_TicksCodeurDroit++;
	  }
}

void COD::CThreadCodeurManager::compterTicGauche (void* p_Ccodeur)
{
	  COD::CThreadCodeurManager* codeurManager = static_cast<COD::CThreadCodeurManager*>(p_Ccodeur);

	  if (digitalRead(PIN_GPIO_SB_GAUCHE) == HIGH)
	  {
		  codeurManager->m_TicksCodeurGauche++;
	  }
	  else
	  {
		  codeurManager->m_TicksCodeurGauche--;
	  }
}*/


