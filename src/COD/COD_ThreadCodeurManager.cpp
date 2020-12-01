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


using namespace std;

COD::CThreadCodeurManager::CThreadCodeurManager()
{
	m_leftTicks = 0;
	m_rightTicks = 0;

	initialisation();
}

COD::CThreadCodeurManager::~CThreadCodeurManager()
{


}

void COD::CThreadCodeurManager::initialisation()
{
	printf("Initialisation codeur\n");

}

void COD::CThreadCodeurManager::readAndReset()
{

}

void COD::CThreadCodeurManager::reset()
{


}

int COD::CThreadCodeurManager::getRightTicks()
{
	return m_rightTicks;
}

int COD::CThreadCodeurManager::getLeftTicks()
{
	return m_leftTicks;
}

