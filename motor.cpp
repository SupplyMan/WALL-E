#include "motor.h"

Motor::Motor(const int speed_pin, const int dir_pin)
{
	this->speed_pin = speed_pin;
	this->dir_pin = dir_pin;
}

void Motor::init()
{
	pinMode(speed_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
}

void Motor::setSpeed(uint8_t speed)
{
	analogWrite(speed_pin, speed);
}

void Motor::setDir(bool dir)
{
	digitalWrite(dir_pin, dir);
}

void Motor::setMotor(uint8_t speed, bool dir)
{
	analogWrite(speed_pin, speed);
	digitalWrite(dir_pin, dir);
}