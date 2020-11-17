/**
 * COF_Strategie.hpp
 * @brief permet de charger la strategie
 */

#ifndef _CONFSTG_
#define _CONFSTG_


namespace COF
{
	/**
	 * @Struct SStrategieDeplacement
	 * @brief structure de la liste des deplacements
	 */
	struct SStrategieDeplacement
	{
		int x;
		int y;
		int angle;
		int vitesse;
		char actions[10];
	};

	/**
	 * @class CConfigurationRobot
	 * @brief Configuration des robot
     **/
	class CStrategieDeplacement
	{
		public:
			/**
			* @brief Constructeur
			* @param[in] p_csvStrategieDeplacementFile : nom du fichier de stategie
			*/
		   CStrategieDeplacement(char * p_csvStrategieDeplacementFile);

			/**
			* @brief Destructeur
		    */
			virtual ~CStrategieDeplacement();

			/**
			* @brief retourne la structure de la strategie de deplacement
			* @return SStrategieDeplacement
			*/
			SStrategieDeplacement* getStrategieDeplacement(int p_index);

			int getSizeStrategie();

		private:

			/**
			* @brief read csv
			*/
			void readCsv();

			char m_csvStrategieDeplacementFile[20]; //< nom du fichier de stategie
			SStrategieDeplacement m_strategieDeplacementStruct[]; //< structure de la strategie de deplacement
		};
}

#endif /* _CONFSTG_ */
