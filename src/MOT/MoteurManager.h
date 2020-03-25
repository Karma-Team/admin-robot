/*#pragma once

#include <cstdint>
#include <cstdio>

/// @brief Fonction utilitaire permettant de calculer l'ordre I2C d'un moteur
///
/// @param arr Valeur en marche arrière, de 0 à 255
/// @param avt Valeur en marche avant, de 0 à 255
///
/// @return Ordre de commande I2C, de 0 à 255
uint8_t calculerOrdre(int arr, int avt);

class MoteurManager
{

public:
	MoteurManager(int i2c_fd);

	void gauchePWM(int arr, int avt);
	void droitePWM(int arr, int avt);
	bool debug=false;
	void stop();

	void apply();

	uint8_t getOrdreGauche() const;
	uint8_t getOrdreDroit() const;
	bool dummy = false;
	bool dummyBlocage = false;

private:
	uint8_t ordreGauche;
	uint8_t ordreDroit;

	int i2c_fd;
};
*/
