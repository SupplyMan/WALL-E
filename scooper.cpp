#include "motor.h"
#include "scooper.h"

Scooper::Scooper(Motor* actuator_left, Motor* actuator_right, Motor* wrist_left, Motor* wrist_right, int limit_switch_left, int limit_switch_right)
{
	this->actuator_left = actuator_left;
	this->actuator_right = actuator_right;
	this->wrist_left = wrist_left;
	this->wrist_right = wrist_right;

	this->limit_switch_left = limit_switch_left;
	this->limit_switch_right = limit_switch_right;
}

void Scooper::arms_up(uint32_t duration_ms)
{
	actuator_left->setMotor(255, false);
	actuator_right->setMotor(255, true);

	delay(duration_ms);

	actuator_left->setSpeed(0);
	actuator_right->setSpeed(0);
}

void Scooper::arms_down(uint32_t duration_ms)
{
	actuator_left->setMotor(255, true);
	actuator_right->setMotor(255, false);

	delay(duration_ms);

	actuator_left->setSpeed(0);
	actuator_right->setSpeed(0);
}

void Scooper::scoop_open()
{

}

void Scooper::scoop_close()
{
	bool left = false;
	bool right = false;

	//wrist_left->setMotor(255, true);
	//wrist_left->setMotor(255, true);

	while (!left || !right)
	{
		if (digitalRead(limit_switch_left) == LOW && !left)
		{
			//wrist_left->setSpeed(0);
			left = true;
		}

		if (digitalRead(limit_switch_right) == LOW && !right)
		{
			//wrist_right->setSpeed(0);
			right = true;
		}
	}
}

void Scooper::scoop()
{
	//scoop_open();
	//arms_down(26000);
	scoop_close();
	//arms_up(26000);
}

void Scooper::init()
{
	actuator_left->init();
	actuator_right->init();
	wrist_left->init();
	wrist_right->init();

	pinMode(limit_switch_left, INPUT_PULLUP);
	pinMode(limit_switch_right, INPUT_PULLUP);
}

void Scooper::calibrate()
{
	arms_up();
	//scoop_close();
}
