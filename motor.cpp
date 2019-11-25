#include "motor.h"

Motor::Motor(const int speedPin, const int dirPin)
{
	this->speedPin = speedPin;
	this->dirPin = dirPin;
}

void Motor::init()
{
	pinMode(speedPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
}

void Motor::setSpeed(uint8_t speed)
{
	analogWrite(this->speedPin, speed);
}

void Motor::setDir(bool dir)
{
	digitalWrite(this->dirPin, dir);
}

void Motor::setMotor(uint8_t speed, bool dir)
{
	analogWrite(this->speedPin, speed);
	digitalWrite(this->dirPin, dir);
}