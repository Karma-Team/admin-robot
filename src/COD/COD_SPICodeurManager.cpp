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


unsigned int nextTime ;
int count = 1;
int fd ;

COD::CSPICodeurManager::CSPICodeurManager(char* p_codeurSerieTty)
{
	snprintf(m_codeurSerieTty, sizeof(m_codeurSerieTty), "/dev/%s", p_codeurSerieTty);
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
		return -1;
	}
	std::cout << "SPI communication successfully setup.\n";

}

void COD::CSPICodeurManager::readAndReset()
{
	unsigned char buffer[2] = { 1, 0 };
	wiringPiSPIDataRW(SPI_CHANNEL, buffer, 2);
	std::cout << "Codeur Droit : " << +buffer[1] << "\n";
	m_rightTicks = +buffer[1];

	unsigned char buffer[2] = { 2, 0 };
	wiringPiSPIDataRW(SPI_CHANNEL, buffer, 2);
	std::cout << "Codeur Gauche : " << +buffer[1] << "\n";
	m_leftTicks = +buffer[1];

	reset();
}

void COD::CSPICodeurManager::reset()
{
	unsigned char buffer[2] = { 3, 0 };
	wiringPiSPIDataRW(SPI_CHANNEL, buffer, 2);
	std::cout << "RESET CODEUR : " << +buffer[1] << "\n";
}

int COD::CSPICodeurManager::getRightTicks()
{
	return m_rightTicks;
}

int COD::CSPICodeurManager::getLeftTicks()
{
	return m_leftTicks;
}

