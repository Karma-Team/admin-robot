/**
 * COF_ConfigurationRobot.hpp
 * @brief permet de charger la configuration du robot au demarrage
 */

#ifndef _CONFCONFIG_
#define _CONFCONFIG_

#include "TCP/TCP_Common.hpp"

namespace COF
{
	/**
	 * @Struct SConfigRobot
	 * @brief structure des elements de configuration du robot
	 */
	struct SConfigRobot
	{
		char ipTcpServeur[16]; // ip Serveur tcp
		double pidKpA; //< P asservissement Angle
		double pidKiA; //< I asservissement Angle
		double pidKdA; //< D asservissement Angle

		double pidKpD; //< P asservissement Direction
		double pidKiD; //< I asservissement Direction
		double pidKdD; //< D asservissement Direction

		double pidKpP; //< P asservissement Position
		double pidKiP; //< I asservissement Position
		double pidKdP; //< D asservissement Position

		double coeffLongueurRoueGauche; //< Coefficient de longeur pour la roue gauche
		double coeffLongueurRoueDroite; //< Coefficient de longeur pour la roue droite
		double coeffAngleRoueGauche; //< Coefficient d'angle pour la roue gauche
		double coeffAngleRoueDroite; //< Coefficient d'angle pour la roue droite

		int moteursI2cAddr;	//< addresse i2c du controleur moteur
		char codeurSerieTty[13]; //< nom du device serie des codeurs
		char servoSerieTty[13]; //< nom du device serie des servos

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
			//CConfigurationRobot(char * p_csvConfigFile);

			/**
			 * @brief Retourne l'instance unique de la classe (singleton)
			 * @return Singleton de la classe
			 **/
			static CConfigurationRobot* inst();

			/**
			 * @brief Destructeur
			 */
			//virtual ~CConfigurationRobot();

			/**
			 * @brief retourne la structure de la configuration du robot
			 * @return SConfigRobot
			 */
			SConfigRobot* getConfRobot();

			/**
			 * @brief read csv
			 */
			void readCsv(char * p_csvConfigFile);


		private:

			/**
			 * @brief Constructeur
			 */
			CConfigurationRobot();

			/**
			 * @breif Constructeur par recopie
			 * @param[in] source : source de la copie
			 **/
			CConfigurationRobot(const CConfigurationRobot &source);

			/**
			 * @brief Operateur d'affectation prive pour interdire son utilisation
			 * @param[in] source : source de la copie
			 **/
			CConfigurationRobot& operator=(const CConfigurationRobot &source);


			//char m_csvConfigFileName[20]; //< nom du fichier csv de la configuration robot
			SConfigRobot m_configRobotStruc; //< copnfiguration du robot dans la structure



	};
}

#endif /* _CONFCONFIG_ */
