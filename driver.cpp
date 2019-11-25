#include "motor.h"
#include "driver.h"

Driver::Driver(Motor* front_left, Motor* front_right, Motor* back_left, Motor* back_right)
{
	this->front_left = front_left;
	this->front_right = front_right;
	this->back_left = back_left;
	this->back_right = back_right;
}

void Driver::init()
{
	front_left->init();
	front_right->init();
	back_left->init();
	back_right->init();
}

void Driver::drive(uint8_t speed, uint8_t dir)
{
	bool front_left_dir, front_right_dir, back_left_dir, back_right_dir;

	switch (dir)
	{
		case Driver::DRIVE_FORWARD:
			front_left_dir = true;
			front_right_dir = true;
			back_left_dir = true;
			back_right_dir = true;
			break;

		case Driver::DRIVE_RIGHT:
			front_left_dir = true;
			front_right_dir = false;
			back_left_dir = false;
			back_right_dir = true;
			break;

		case Driver::DRIVE_BACKWARD:
			front_left_dir = false;
			front_right_dir = false;
			back_left_dir = false;
			back_right_dir = false;
			break;

		case Driver::DRIVE_LEFT:
			front_left_dir = false;
			front_right_dir = true;
			back_left_dir = true;
			back_right_dir = false;
			break;
	}

	front_left->setMotor(speed, front_left_dir);
	front_right->setMotor(speed, front_right_dir);
	back_left->setMotor(speed, back_left_dir);
	back_right->setMotor(speed, back_right_dir);
}

void Driver::rotate(uint8_t speed, uint8_t dir)
{
	bool front_left_dir, front_right_dir, back_left_dir, back_right_dir;

	if (dir)
	{
		front_left_dir = true;
		front_right_dir = false;
		back_left_dir = true;
		back_right_dir = false;
	}
	else
	{
		front_left_dir = false;
		front_right_dir = true;
		back_left_dir = false;
		back_right_dir = true;
	}

	front_left->setMotor(speed, front_left_dir);
	front_right->setMotor(speed, front_right_dir);
	back_left->setMotor(speed, back_left_dir);
	back_right->setMotor(speed, back_right_dir);
}

void Driver::setSpeed(uint8_t speed)
{
	front_left->setSpeed(speed);
	front_right->setSpeed(speed);
	back_left->setSpeed(speed);
	back_right->setSpeed(speed);
}

void Driver::stop()
{
	this->setSpeed(0);
}