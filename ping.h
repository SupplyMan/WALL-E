#ifndef _PING_H
#define _PING_H

#include <Arduino.h>

class Ping
{
private:
	int trig_pin;
	int echo_pin;

	int32_t ping();

public:
	Ping(const int trig_pin, const int echo_pin);
	void init();
	int getCentimeters();
	int getInches();
};

#endif