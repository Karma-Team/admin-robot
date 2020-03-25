/*
#include "MoteurManager.h"

#include <iostream>
#include <cstdio>
#include <unistd.h>

using namespace std;

uint8_t calculerOrdreI2C(int arr, int avt)
{
	// Notes pour l’envoi en I2C pour être compatible avec les ponts en H I2C:
	//
	// 0..127 = marche arrière
	// 128 = 0
	// 129..255 = marche avant
	
	

	return 128 - ((arr+1) / 2 ) + (avt / 2); //true
}

// Constructeur par défaut : on stoppe les moteurs
MoteurManager::MoteurManager(int i2c) :
	ordreGauche(128),
	ordreDroit(128),
	i2c_fd(i2c)
{

}

// Changement de consigne sur les moteurs

void MoteurManager::gauchePWM(int arr, int avt)
{
	ordreGauche = calculerOrdreI2C(arr, avt);
}

void MoteurManager::droitePWM(int arr, int avt)
{
	ordreDroit = calculerOrdreI2C(arr, avt);
}


void MoteurManager::stop()
{
	ordreGauche = 128;
	ordreDroit = 128;
}

// Envoi effectif en I2C des commandes

void MoteurManager::apply()
{
	//0if(debug){
		//std::cerr << "manager::apply " << (int) ordreGauche << " " << (int) ordreDroit << std::endl;
		//}

	// Les deux octets que l’on va envoyer en I2C
	uint8_t data[2];

	data[0] = ordreGauche;
	data[1] = ordreDroit;

	// Envoi du tableau de deux octets
	if(dummy == false && !dummyBlocage)
		write(i2c_fd, data, 2);
}

// Getters

uint8_t MoteurManager::getOrdreGauche() const
{
	return ordreGauche;
}

uint8_t MoteurManager::getOrdreDroit() const
{
	return ordreDroit;
}
*/
