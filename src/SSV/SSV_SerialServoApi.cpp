#include "SSV_SerialServoApi.hpp"


SSV::CSerialServoApi::CSerialServoApi(string  p_usbPort, uint32_t p_baud)
{
	m_pilotageServo =  CLx16a(p_usbPort, p_baud);
	if(m_pilotageServo.initDeviceSerialPort() == -1)
	{
		printf("Port Serie non init servo Stop Programme");
		exit(1);
	}
}


SSV::CSerialServoApi::~CSerialServoApi()
{
	// rien a faire
}

bool SSV::CSerialServoApi::activerServoAngle(uint32_t p_idServo, double p_angle, uint32_t p_timeout)
{
	bool valide = false;
	uint32_t time = 0;
	signed short positionServo;
	
	while(m_pilotageServo.getBusyFlag() != true);
	m_pilotageServo.readDeviceSerialPort(p_idServo, SSV_SERVO_MESSAGE_POS_READ, &positionServo);

	// envoie de la nouvelle position
	m_parameters[0] = p_angle;
	
	while(m_pilotageServo.getBusyFlag() != true);
	m_pilotageServo.writeDeviceSerialPort(p_idServo, SSV_SERVO_MESSAGE_MOVE_TIME_WRITE, m_parameters);


	while((positionServo != p_angle) && (time < p_timeout))
	{
		while(m_pilotageServo.getBusyFlag() != true);
		m_pilotageServo.readDeviceSerialPort(p_idServo, SSV_SERVO_MESSAGE_POS_READ, &positionServo);
		time++;
		usleep(1 * 1000);
	}

	valide = true;
	return valide;
}

bool SSV::CSerialServoApi::activerServoMoteur(uint32_t p_idServo, double p_speed, uint32_t p_timeout)
{
	uint32_t time = 0;

	// envoie de la nouvelle vitesse
	m_parameters[0] = p_speed;
	
	while(m_pilotageServo.getBusyFlag() != true);
	m_pilotageServo.writeDeviceSerialPort(p_idServo, SSV_SERVO_MESSAGE_OR_MOTOR_MODE_WRITE, m_parameters);

	while(time < p_timeout)
	{
		time++;
		usleep(1 * 1000);
	}

	// Arret du moteur
	m_parameters[0] = 0;
	
	while(m_pilotageServo.getBusyFlag() != true);
	m_pilotageServo.writeDeviceSerialPort(p_idServo, SSV_SERVO_MESSAGE_OR_MOTOR_MODE_WRITE, m_parameters);

	return true;
}

