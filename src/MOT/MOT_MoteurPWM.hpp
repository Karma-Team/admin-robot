#include <unistd.h>
#include <stdint.h>

#ifndef _MOTMOTEURPWM_
#define _MOTMOTEURPWM_

namespace MOT
{
	class CMoteurPWM
	{

		public:

		      /**
		       * @brief Retourne l'instance unique de la classe (singleton)
		       * @return Singleton de la classe
		       **/
		       static CMoteurPWM* inst();

		       /**
			* Destructeur
			**/
			void init();

		      /**
		       * @brief envoie des commandes aux moteurs
		       * @param[in] p_dArr : consigne droite arriere
		       * @param[in] p_dAvt : consigne droite avant
		       * @param[in] p_gArr : consigne gauche arriere
		       * @param[in] p_gAvt : consigne droite avant
		       */
		       void setMoteurSpeed(int p_dArr, int p_dAvt, int p_gArr, int p_gAvt);


			private:

				  /**
		       * @brief Constructeur
		       **/
		      CMoteurPWM();

		      /**
		       * @breif Constructeur par recopie
		       * @param[in] source : source de la copie
		       **/
		      CMoteurPWM(const CMoteurPWM& source);

		      /**
		       * @brief Operateur d'affectation prive pour interdire son utilisation
		       * @param[in] source : source de la copie
		       **/
		      CMoteurPWM& operator=(const CMoteurPWM& source);

		      /**
		       * @brief application de la PWM sur le moteur de droit
		       * @param[in] p_inAv : consigne avant 
		       * @param[in] p_inArr : consigne arriere 
		       **/
		      void setMoteurSpeedDroite(int p_inAv, int p_inArr);


		      /**
		       * @brief application de la PWM sur le moteur de Gauche
		       * @param[in] p_inAv : consigne avant 
		       * @param[in] p_inArr : consigne arriere 
		       **/
		      void setMoteurSpeedGauche(int p_inAv, int p_inArr);
    
	};
}

#endif /* _MOTMOTEURPWM_ */
