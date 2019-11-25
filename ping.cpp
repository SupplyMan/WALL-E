#include "ping.h"

Ping::Ping(int trig_pin, int echo_pin)
{
	this->trig_pin = trig_pin;
	this->echo_pin = echo_pin;
}

void Ping::init()
{
	pinMode(trig_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
}

int32_t Ping::ping()
{
	digitalWrite(trig_pin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig_pin, LOW);

	return pulseIn(echo_pin);
}

int Ping::getCentimeters()
{
	return getDuration() * 0.034 / 2;
}

int Ping::getInches()
{
	return getDuration() * 0.0133 / 2;
}