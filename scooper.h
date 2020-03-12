#ifndef _SCOOPER_H
#define _SCOOPER_H

#include <Arduino.h>

class Scooper
{
private:
	Motor* actuator_left;
	Motor* actuator_right; 
	Motor* wrist_left;
	Motor* wrist_right;

	int limit_switch_left;
	int limit_switch_right;

	void arms_up(uint32_t duration_ms);
	void arms_down(uint32_t duration_ms);
	void scoop_open();
	void scoop_close();

public:
	Scooper(Motor* actuator_left, Motor* actuator_right, Motor* wrist_left, Motor* wrist_right, int limit_switch_left, int limit_switch_right);
	void init();
	void calibrate();
	void scoop();
};

#endif