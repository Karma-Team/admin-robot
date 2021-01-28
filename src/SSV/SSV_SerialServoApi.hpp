/**
 * SSV_SerialServoApi.hpp
 */
#include <iostream>
#include "SSV/SSV_ReadWrite.hpp"

namespace SSV
{
	class CSerialServoApi
	{
		public:
			CSerialServoApi(string  p_usbPort, uint32_t p_baud);
			virtual ~CSerialServoApi();

			bool activerServoAngle(uint32_t p_idServo, double p_angle, uint32_t p_timeout);
			bool activerServoMoteur(uint32_t p_idServo, double p_speed, uint32_t p_timeout);
		
			CLx16a* getInstanceDriverSSV();

		private:
			CLx16a		m_pilotageServo;
			string 		m_inputMsg;
			double		m_parameters[SSV_PARAMETERS_NB_MAX];

	};
}
