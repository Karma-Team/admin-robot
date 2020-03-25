/*
#include "SerialCodeurManager.h"

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
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;


int arduino;
unsigned int nextTime ;
int count = 1;
int fd ;

SerialCodeurManager::SerialCodeurManager(int init) :
	 initCodeur(init)
{

}

void SerialCodeurManager::CloseS()
{
	serialClose(fd);
	printf("Close serial\n");
}

void SerialCodeurManager::Initialisation()
{
	printf("Initialisation codeur\n");
	
	if ((fd = serialOpen ("/dev/ttyUSB0", 115200)) < 0)
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

void SerialCodeurManager::readAndReset()
{
	
		int ticks[4];
		char SerieData = ' ';
		char tickChar [10000];
		char tickd [10000];
		char tickg [10000];
		int dataAvail = 0;
		int i = 0;
		int s = 0;
		bool G = false;
		bool D = false;

		bool G1 = false;
		bool D1 = false;

		int g1 = 0, d1 = 0, g2 = 0, d2 = 0;

		memset(tickChar, ' ', 10000);
		memset(tickd, ' ', 10000);
		memset(tickg, ' ', 10000);
				

	  	if (millis () > nextTime)
		{
			//Debuguer
			//printf ("\nOut: %3d: ", count) ;
		    fflush (stdout) ;
		    serialPutchar (fd, 'C') ;
		    nextTime += 10 ;
		    ++count ;
		}

		//delay (10) ;

		while (serialDataAvail (fd))
		{
			SerieData = serialGetchar (fd);
			tickChar[i] = SerieData;
			//Debuguer
		    //printf (" -> %c", serialGetchar (fd)) ;
		    if(SerieData == '?')
		    {
		    	G = true;
		    	D = false;
		    }
		    if(SerieData == '!')
		    {
		    	D = true;
		    	G = false;
		    }

		    if(G == true && D == false)
		    {
		    	if(G1 == false)
		    		g2++;
		    	if(g2 == 2)
		    	{
		    		G1 = true;
		    		tickg[g1] = SerieData;
		    		g1++;

		    	}
		    		
		    }
		    if(G == false && D == true)
		    {
		    	if(D1 == false)
		    		d2++;
		    	if(d2 == 2)
		    	{
		    		D1 = true;
		    		tickd[d1] = SerieData;
		    		d1++;
		    	}
		    }

		    i++;
		    fflush (stdout) ;
		}

		
		i = 0, g1 = 0, d1 = 0, g2 = 0, d2 = 0;

		
		ticks[0] =  atoi(tickd);
		ticks[2] =  atoi(tickd);
		ticks[1] =  atoi(tickg);
		ticks[3] =  atoi(tickg);

		//Debuguer
		//printf ("\n"); 		
		
		//cout << " G:" << ticks[0] <<" D:" << ticks[1] << " G:" << ticks[2] << " D:" << ticks[3] << endl;
		
		
		if(ticks[0] == ticks[2] && ticks[1] == ticks[3])	
		{
			leftTicks = ticks[0];
			rightTicks = ticks[1];
			
		}
		else
		{
			leftTicks = 0;
			rightTicks = 0;	
		}
}

void SerialCodeurManager::reset()
{
	serialPutchar (fd, 'R');
}
*/
