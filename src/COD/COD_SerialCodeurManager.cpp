#include "COD_SerialCodeurManager.hpp"

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
#include <wiringSerial.h>

using namespace std;


unsigned int nextTime ;
int count = 1;
int fd ;

COD::CSerialCodeurManager::CSerialCodeurManager(char* p_codeurSerieTty)
{
	snprintf(m_codeurSerieTty, sizeof(m_codeurSerieTty), "/dev/%s", p_codeurSerieTty);
	m_leftTicks = 0;
	m_rightTicks = 0;

	initialisation();
}

COD::CSerialCodeurManager::~CSerialCodeurManager()
{
	closeS();
}

void COD::CSerialCodeurManager::closeS()
{
	serialClose(fd);
	printf("Close serial\n");
}

void COD::CSerialCodeurManager::initialisation()
{
	printf("Initialisation codeur\n");
	
	if ((fd = serialOpen (m_codeurSerieTty, 115200)) < 0)
		{
		    	fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		    	//return 1 ;
		}

	if (wiringPiSetup () == -1)
		{
		   		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		    	//return 1 ;
		}

	nextTime = millis () + 10 ;
}

void COD::CSerialCodeurManager::readAndReset()
{
		char SerieData = ' ';
		char SerilDataTab[10000] = {0};
		char tickGauche[1000] = {0};
		char tickDroit[1000] = {0};

		int index = 0;
		int serialDataAvailable = 0;

		while (serialDataAvailable <= 4)
		{
			serialPutchar (fd, 'C') ;
			serialDataAvailable = serialDataAvail (fd);
			cout << "serialDataAvail = " << serialDataAvailable << endl;
		}

		while (index < serialDataAvailable)
		{
			SerilDataTab[index] = serialGetchar (fd);
			fflush (stdout) ;
			index++;
		}

		bool codeurDroit = false;
		int j = 0;
		
		for(int i = 0; i < index; i++)
		{
			if(SerilDataTab[i] != '\0')
			{
				if(SerilDataTab[i] == '!')
				{
					codeurDroit = true;
					j = 0;
				}
				if(codeurDroit != true)
				{
					tickGauche[j] = SerilDataTab[i];
					j++;
				}
				else if (SerilDataTab[i] != '!')
				{
					tickDroit[j] =  SerilDataTab[i];
					j++;
				}
			}
			else
			{
				break;
			}

		}

		m_rightTicks = atoi(tickDroit);
		m_leftTicks = atoi(tickGauche);

		reset();
}

void COD::CSerialCodeurManager::reset()
{
	serialPutchar(fd, 'R');
}

int COD::CSerialCodeurManager::getRightTicks()
{
	return m_rightTicks;
}

int COD::CSerialCodeurManager::getLeftTicks()
{
	return m_leftTicks;
}

