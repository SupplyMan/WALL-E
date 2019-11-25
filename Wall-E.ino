#include "motor.h"
#include "driver.h"
#include "cmd_handler.h"

class Scooper
{
private:
	Motor* actuator_left;
	Motor* actuator_right;
	Motor* wrist_left;
	Motor* wrist_right;

public:

};
	
// interrupts can be used on the following pins: 2, 3, 18, 19, 20, 21

// driver 1
// front left
const int M1_SPEED_PIN = 2;
const int M1_DIR_PIN = 24;

// front right
const int M2_SPEED_PIN = 3;
const int M2_DIR_PIN = 26;

// driver 2
// back left
const int M3_SPEED_PIN = 6;
const int M3_DIR_PIN = 28;

// back right
const int M4_SPEED_PIN = 5;
const int M4_DIR_PIN = 30;

// driver 3 (actuators)
// left
const int A1_SPEED_PIN = 7;
const int A1_DIR_PIN = 32;

// right
const int A2_SPEED_PIN = 8;
const int A2_DIR_PIN = 34;

// driver 4 (geared motors)
// left
const int G1_SPEED_PIN = 9;
const int G1_DIR_PIN = 36;

//right
const int G2_SPEED_PIN = 10;
const int G2_DIR_PIN = 38;

Motor front_left(M1_SPEED_PIN, M1_DIR_PIN);
Motor front_right(M2_SPEED_PIN, M2_DIR_PIN);
Motor back_left(M3_SPEED_PIN, M3_DIR_PIN);
Motor back_right(M4_SPEED_PIN, M4_DIR_PIN);

Motor actuator_left(A1_SPEED_PIN, A1_DIR_PIN);
Motor actuator_right(A2_SPEED_PIN, A2_DIR_PIN);
Motor gearbox_left(G1_SPEED_PIN, G1_DIR_PIN);
Motor gearbox_right(G2_SPEED_PIN, G2_DIR_PIN);

Driver driver(&front_left, &front_right, &back_left, &back_right);



SerialCommandHandler sch;

void test_func(char* tokens[], size_t token_count)
{
	for (size_t i = 0; i < token_count; i++)
	{
		Serial.println(tokens[i]);
	}
	Serial.println(token_count, DEC);
}

void drive_func(char* tokens[], size_t token_count)
{
	driver.drive(atoi(tokens[1]), atoi(tokens[2]));
}

void rotate_func(char* tokens[], size_t token_count)
{
	driver.rotate(atoi(tokens[1]), atoi(tokens[2]));
}

void speed_func(char* tokens[], size_t token_count)
{
	driver.setSpeed(atoi(tokens[1]));
}

void stop_func(char* tokens[], size_t token_count)
{
	driver.stop();
}

void setup()
{
	//sch.registerCommand("test", &test_func);
	sch.registerCommand("drive", &drive_func);
	sch.registerCommand("rotate", &rotate_func);
	sch.registerCommand("speed", &speed_func);
	sch.registerCommand("stop", &stop_func);

	sch.init();

	driver.init();
}

void loop()
{
	if (Serial.available())
	{
		sch.handleCommand();
	}
}
