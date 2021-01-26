/*
 * ATL_CsvAtelierDecode.hpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include <iostream>
#include "ODO_Odometrie.hpp"
#include "MOT_MoteurPWM.hpp"

#ifndef _ATL_CSVATELIERDECODE_HPP_
#define _ATL_CSVATELIERDECODE_HPP_


namespace ATL
{
/**
	 * @Struct SCsvAtelier
	 * @brief structure de la liste des action de l'atelier
	 */
	struct SCsvAtelierAction
	{
		uint32_t id;
		char modeServo;
		double vitesseAngleServo;
		uint32_t timeoutServo;
		int vitesseDeplacement;
		int angleDeplacement;
		int xDeplacement;
		int yDeplacement;
		uint32_t timeoutAtelier;
	};

	/**
	 * @class CCsvAtelierDecode
	 * @brief
     **/
	class CCsvAtelierDecode
	{
		public:

			/**
			 * @brief Retourne l'instance unique de la classe (singleton)
			 * @return Singleton de la classe
			 **/
			static CCsvAtelierDecode* inst();


			/**
			* @brief Constructeur
			* @param[in] p_csvAtelierFile : nom du fichier de atelier
			*/
			//CCsvAtelierDecode(char * p_csvAtelierFile);

			/**
			* @brief Destructeur
		    */
			//virtual ~CCsvAtelierDecode();

			/**
			* @brief retourne la structure de l'atelier
			* @return SStrategieDeplacement
			*/
			SCsvAtelierAction* getCsvAtelierAction(int p_index);

			/**
			* @brief read csv
			*/
			void readCsv(char * p_csvAtelierFile);


		private:

			/**
			 * @brief Constructeur
			 */
			CCsvAtelierDecode();

			/**
			 * @breif Constructeur par recopie
			 * @param[in] source : source de la copie
			 **/
			CCsvAtelierDecode(const CCsvAtelierDecode &source);

			/**
			 * @brief Operateur d'affectation prive pour interdire son utilisation
			 * @param[in] source : source de la copie
			 **/
			CCsvAtelierDecode& operator=(const CCsvAtelierDecode &source);

			//char m_csvAtelierDecodeFile[20]; //< nom du fichier
			SCsvAtelierAction m_scsvAtelierAction;
			int m_index;

		};
}



#endif /* _ATL_CSVATELIERDECODE_HPP_ */
