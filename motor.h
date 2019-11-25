#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

class Motor 
{
private:
	int speedPin;
	int dirPin;

public:
	Motor(const int speedPin, const int dirPin);

	void init();
	void setSpeed(uint8_t speed);
	void setDir(bool dir);
	void setMotor(uint8_t speed, bool dir);
};

#endif