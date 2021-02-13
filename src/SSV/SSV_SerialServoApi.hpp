/**
 * SSV_SerialServoApi.hpp
 */
#ifndef _CSERIALSERVOAPI_
#define _CSERIALSERVOAPI_

#include <iostream>
#include "SSV/SSV_ReadWrite.hpp"
#include <string.h>


namespace SSV
{
	class CSerialServoApi
	{
		public:
			CSerialServoApi(std::string  p_usbPort, uint32_t p_baud);
			virtual ~CSerialServoApi();

			bool activerServoAngle(uint32_t p_idServo, double p_angle, uint32_t p_timeout);
			bool activerServoMoteur(uint32_t p_idServo, double p_speed, uint32_t p_timeout);
		
			CLx16a* getInstanceDriverSSV();

		private:
			SSV::CLx16a	*	m_pilotageServo;
			std::string		m_inputMsg;
			double			m_parameters[SSV_PARAMETERS_NB_MAX];

	};
}

#endif
