#include "COD_SPICodeurManager.hpp"

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
#include <wiringPiSPI.h>

using namespace std;

COD::CSPICodeurManager::CSPICodeurManager()
{
	m_leftTicks = 0;
	m_rightTicks = 0;

	initialisation();
}

COD::CSPICodeurManager::~CSPICodeurManager()
{
	closeS();
}

void COD::CSPICodeurManager::closeS()
{
	printf("Close serial\n");
}

void COD::CSPICodeurManager::initialisation()
{
	printf("Initialisation codeur\n");
	
	int fd = wiringPiSPISetupMode(SPI_CHANNEL, SPI_CLOCK_SPEED, 0);
	if (fd == -1)
	{
		std::cout << "Failed to init SPI communication.\n";
		exit(1);
	}
	std::cout << "SPI communication successfully setup.\n";

}

void COD::CSPICodeurManager::readAndReset()
{
	unsigned char bufferD[3] = { 'd', 0};
	wiringPiSPIDataRW(SPI_CHANNEL, bufferD, 2);
	std::cout << "Codeur Droit : " << bufferD[1] << "\n";
	m_rightTicks = bufferD[1];
	
	
	unsigned char bufferG[3] = { 'g', 0};
	wiringPiSPIDataRW(SPI_CHANNEL, bufferG, 2);
	std::cout << "Codeur Gauche : " << bufferG[1] << "\n";
	m_leftTicks = bufferG[2];

	reset();
}

void COD::CSPICodeurManager::reset()
{
	unsigned char bufferR[2] = { 'r', 0 };
	wiringPiSPIDataRW(SPI_CHANNEL, bufferR, 2);
}

int COD::CSPICodeurManager::getRightTicks()
{
	return m_rightTicks;
}

int COD::CSPICodeurManager::getLeftTicks()
{
	return m_leftTicks;
}

