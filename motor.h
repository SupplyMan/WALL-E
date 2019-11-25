#ifndef _MOTOR_H
#define _MOTOR_H

#include <Arduino.h>

class Motor 
{
private:
	int speed_pin;
	int dir_pin;

public:
	Motor(const int speed_pin, const int dir_pin);

	void init();
	void setSpeed(uint8_t speed);
	void setDir(bool dir);
	void setMotor(uint8_t speed, bool dir);
};

#endif