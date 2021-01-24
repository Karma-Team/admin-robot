/*
 * ASV_Asserv.hpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#include "ODO_Odometrie.hpp"
#include "MOT_MoteurPWM.hpp"
#include "ATL_CsvAtelierDecode.hpp"

#ifndef _ASV_ASSERV_HPP_
#define _ASV_ASSERV_HPP_


namespace ATL
{
	class CAtelier
	{
		public:

			CAtelier();

			virtual ~CAtelier();

			void actionAtelier(SCsvAtelierAction p_scsvAtelierAction );

			void debug();

		private:

	};
}



#endif /* _ASV_Asserv_HPP_ */
