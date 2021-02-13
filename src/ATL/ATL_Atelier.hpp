/*
 * ASV_Asserv.hpp
 *
 *  Created on: 19 nov. 2020
 *      Author: thomas
 */

#ifndef _ATL_ATELIER_HPP_
#define _ATL_ATELIER_HPP_

#include "ODO_Odometrie.hpp"
#include "MOT_MoteurPWM.hpp"
#include "ATL_CsvAtelierDecode.hpp"


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
