#include "MOT_MoteurManager.hpp"

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <wiringPiI2C.h>

using namespace std;

MOT::CMoteurManager* MOT::CMoteurManager::inst()
{
  static CMoteurManager m_singleton;
  
  return(&m_singleton);
}

MOT::CMoteurManager::CMoteurManager()
{
  //rien a faire
}

// Constructeur par défaut : on stoppe les moteurs
void MOT::CMoteurManager::init(int p_i2cAddrMoteur)
{
	m_ordreGauche = 128;
	m_ordreDroit =  128;
	m_i2cAddrMoteur = wiringPiI2CSetup(p_i2cAddrMoteur);

	//Arret des moteurs
	apply();

}

MOT::CMoteurManager::~CMoteurManager()
{
	//rien a faire
}

uint8_t MOT::CMoteurManager::calculerOrdreI2c(int p_arr, int p_avt)
{
	// Notes pour l’envoi en I2C pour être compatible avec les ponts en H I2C:
	//
	// 0..127 = marche arrière
	// 128 = 0
	// 129..255 = marche avant
	

	return 128 - ((p_arr+1) / 2 ) + (p_avt / 2); //true
}

// Changement de consigne sur les moteurs

void MOT::CMoteurManager::gauchePWM(int p_arr, int p_avt)
{
	m_ordreGauche = calculerOrdreI2c(p_arr, p_avt);
}

void MOT::CMoteurManager::droitePWM(int p_arr, int p_avt)
{
	m_ordreDroit = calculerOrdreI2c(p_arr, p_avt);
}


void MOT::CMoteurManager::stop()
{
	m_ordreGauche = 128;
	m_ordreDroit = 128;
}

// Envoi effectif en I2C des commandes

void MOT::CMoteurManager::apply()
{
	//0if(debug){
		//std::cerr << "manager::apply " << (int) ordreGauche << " " << (int) ordreDroit << std::endl;
		//}

	// Les deux octets que l’on va envoyer en I2C
	uint8_t data[2];

	data[0] = m_ordreGauche;
	data[1] = m_ordreDroit;

	// Envoi du tableau de deux octets
	if(dummy == false && !dummyBlocage) write(m_i2cAddrMoteur, data, 2);
}

// Getters

uint8_t MOT::CMoteurManager::getOrdreGauche() const
{
	return m_ordreGauche;
}

uint8_t MOT::CMoteurManager::getOrdreDroit() const
{
	return m_ordreDroit;
}

