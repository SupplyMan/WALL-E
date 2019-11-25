#ifndef DRIVER_H_
#define DRIVER_H_

#include <Arduino.h>

class Driver 
{
private:
	Motor* front_left;
	Motor* front_right;
	Motor* back_left;
	Motor* back_right;

public:
	Driver(Motor* front_left, Motor* front_right, Motor* back_left, Motor* back_right);

	void init();
	void drive(uint8_t speed, uint8_t dir);
	void rotate(uint8_t speed, uint8_t dir);
	void setSpeed(uint8_t speed);
	void stop();

	static const uint8_t DRIVE_FORWARD = 0;
	static const uint8_t DRIVE_RIGHT = 1;
	static const uint8_t DRIVE_BACKWARD = 2;
	static const uint8_t DRIVE_LEFT = 3;
};

#endif