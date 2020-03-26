#include <unistd.h>
#include <stdint.h>

#ifndef _MOTMOTEUR_
#define _MOTMOTEUR_

namespace MOT
{
	class CMoteurManager
	{

		public:

			/**
			 * Constructeur
			 */
			CMoteurManager(int p_i2cAddrMoteur);

			/**
			 * Destructeur
			 */
			virtual ~CMoteurManager();

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

			/**
			 * @brief calculerOrdre au moteur
			 */
			uint8_t calculerOrdreI2c(int p_arr, int p_avt);

			bool debug=false; //< mettre le debug
			bool dummy = false;
			bool dummyBlocage = false;

	private:

		uint8_t m_ordreGauche;//< ordre moteur gauche PWM

		uint8_t m_ordreDroit;//< ordre moteur droite PWM

		int m_i2cAddrMoteur;//< addresse i2c
	};
}

#endif /* _CONFCONFIG_ */