/**
 * COF_ConfigurationRobot.hpp
 * @brief permet de charger la configuration du robot au demarrage
 */

#ifndef _CONFCONFIG_
#define _CONFCONFIG_

namespace COF
{
	/**
	 * @Struct SConfigRobot
	 * @brief structure des elements de configuration du robot
	 */
	struct SConfigRobot
	{
		double pidKpA; //< P asservissement
		double pidKiA; //< I asservissement
		double pidKdA; //< D asservissement

		double coeffLongueurRoueGauche; //< Coefficient de longeur pour la roue gauche
		double coeffLongueurRoueDroite; //< Coefficient de longeur pour la roue droite
		double coeffAngleRoueGauche; //< Coefficient d'angle pour la roue gauche
		double coeffAngleRoueDroite; //< Coefficient d'angle pour la roue droite

		int moteursI2cAddr;	//< addresse i2c du controleur moteur
		char codeurSerieTty[8]; //< nom du device serie des codeurs
		char servoSerieTty[8]; //< nom du device serie des servos

	};

	/**
		@class CConfigurationRobot
		@brief Configuration des robot
	 **/
	class CConfigurationRobot
	{
		public:

			/**
			 * @brief Constructeur
			 * @param[in] p_csvConfigFile : nom du fichier de config a lire
			 */
			CConfigurationRobot(char * p_csvConfigFile);

			/**
			 * @brief Destructeur
			 */
			virtual ~CConfigurationRobot();

			/**
			 * @brief retourne la structure de la configuration du robot
			 * @return SConfigRobot
			 */
			SConfigRobot getConfRobot();


		private:

			/**
			 * @brief read csv
			 */
			void readCsv();

			char m_csvConfigFileName[20]; //< nom du fichier csv de la configuration robot
			SConfigRobot m_configRobotStruc; //< copnfiguration du robot dans la structure



	};
}

#endif /* _CONFCONFIG_ */
