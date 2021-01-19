#include <unistd.h>
#include <stdint.h>

#define MGinARR 12//moteur gauche arrière
#define MGinAV  16 //moteur gauche avant
#define MDinAV  20  //moteur droit avant
#define MDinARR 21  //moteur droit arrière

#define AV 1 //indexs pour les tableaux de retour de la fonction de conversion
#define ARR 0

#define END 7
#define ENG 8

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
		
		protected:
		
			/** 
			  * @brief Verfication des bornes de la variable
			  * @param[in] p_min : minimum
			  * @param[in] p_val : valeur a tester
			  * @param[in] p_mac : maximum
			  * @return true valeur valide entre les borne false sinon
			  **/
			bool isBetween(int p_min, int p_val, int p_max);
		
		
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
