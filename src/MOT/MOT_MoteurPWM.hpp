#include <unistd.h>
#include <stdint.h>

#define PwmMoteurDroite 13 		     // 33
#define SensRotationPointHGrosDir1 6 // 31
#define SensRotationADroiteIn1  6    // In1 31
#define SensRotationBDroiteIn2  5    // In2 29

#define PwmMoteurGauche  12 		  // 32
#define SensRotationPointHGrosDir2 16 // 36
#define SensRotationAGaucheIn3  16    // In3 31
#define SensRotationBGaucheIn4  20    // In4 38

//  			|Arrêt (moteur libre)| 	Sens + 	|	Sens – 	|Arrêt (moteur freiné)|
//   			|					 |			|			|					  |
//In1 	In3 	|        LOW 		 |	 HIGH 	|	LOW 	|		HIGH		  |
//In2 	In4 	|        LOW 		 |	 LOW 	|	HIGH 	|		HIGH		  |

#ifndef _MOTMOTEURPWM_
#define _MOTMOTEURPWM_

namespace MOT
{
	class CMoteurPWM
	{

		public:

			/**
			 * @brief Constructeur
			 */
			CMoteurPWM();

			/**
			 * @brief Destructeur
			 */
			~CMoteurPWM();

			/**
			 * @brief initialisation
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
