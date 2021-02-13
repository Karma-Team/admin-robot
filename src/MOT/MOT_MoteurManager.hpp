#ifndef _MOTMOTEURMANAGER_
#define _MOTMOTEURMANAGER_


#include <unistd.h>
#include <stdint.h>


namespace MOT {
class CMoteurManager {

public:
	/**
	 * @brief Retourne l'instance unique de la classe (singleton)
	 * @return Singleton de la classe
	 **/
	static CMoteurManager* inst();

	/**
	 * init
	 */
	void init(int p_i2cAddrMoteur);

	/**
	 * @brief commande moteur gauche PWM
	 */
	void gauchePWM(int p_arr, int p_avt);

	/**
	 * @brief commande moteur droite PWM
	 */
	void droitePWM(int p_arr, int p_avt);

	/**
	 * @brief Stopper les moteurs
	 */
	void stop();

	/**
	 * @brief  Appliquer les nouvelle commandes
	 */
	void apply();

	/**
	 * @brief recuperation des ordres de commande gauche
	 */
	uint8_t getOrdreGauche() const;

	/**
	 * @brief recuperation des ordres de commande droite
	 */
	uint8_t getOrdreDroit() const;

protected:
	/**
	 * @brief calculerOrdre au moteur
	 */
	uint8_t calculerOrdreI2c(int p_arr, int p_avt);

	bool debug = false; //< mettre le debug
	bool dummy = false;
	bool dummyBlocage = false;

private:

	/**
	 * @brief Constructeur
	 */
	CMoteurManager();

	/**
	 * @breif Constructeur par recopie
	 * @param[in] source : source de la copie
	 **/
	CMoteurManager(const CMoteurManager &source);

	/**
	 * @brief Operateur d'affectation prive pour interdire son utilisation
	 * @param[in] source : source de la copie
	 **/
	CMoteurManager& operator=(const CMoteurManager &source);

	uint8_t m_ordreGauche; //< ordre moteur gauche PWM

	uint8_t m_ordreDroit; //< ordre moteur droite PWM

	int m_i2cAddrMoteur; //< addresse i2c
};
}

#endif /* _CONFCONFIG_ */
