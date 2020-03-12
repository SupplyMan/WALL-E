#include "motor.h"
#include "driver.h"
#include "cmd_handler.h"
#include "ping.h"
#include "scooper.h"

/*
typedef void (*EventCallback)(void);

class Event
{
private:
	EventCallback func;
	uint32_t last_tick;

public:
	Event(Event)

};

class Timer
{
private:
	static const MAX_EVENTS = 10;
	Event events[MAX_EVENTS];

public:
	int8_t repeat();
	int8_t once();

	void stop(int8_t id);
	void update();
};

int8_t Timer::repeat();
*/


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

// driver 3 (geared motors)
// left
const int G1_SPEED_PIN = 7;
const int G1_DIR_PIN = 32;

// right
const int G2_SPEED_PIN = 8;
const int G2_DIR_PIN = 34;

// switches
const int LIMIT_SWITCH_LEFT = 31;
const int LIMIT_SWITCH_RIGHT = 33;

// driver 4 (actuators)
// left
const int A1_SPEED_PIN = 9;
const int A1_DIR_PIN = 36;

//right
const int A2_SPEED_PIN = 10;
const int A2_DIR_PIN = 38;

// ultrasonic sensors
const int PING_CENTER_TRIG_PIN = 40;
const int PING_CENTER_ECHO_PIN = 42;

const int PING_LEFT_TRIG_PIN = 44;
const int PING_LEFT_ECHO_PIN = 46;

const int PING_RIGHT_TRIG_PIN = 48;
const int PING_RIGHT_ECHO_PIN = 50;

Motor front_left(M1_SPEED_PIN, M1_DIR_PIN);
Motor front_right(M2_SPEED_PIN, M2_DIR_PIN);
Motor back_left(M3_SPEED_PIN, M3_DIR_PIN);
Motor back_right(M4_SPEED_PIN, M4_DIR_PIN);

Motor actuator_left(A1_SPEED_PIN, A1_DIR_PIN);
Motor actuator_right(A2_SPEED_PIN, A2_DIR_PIN);
Motor gearbox_left(G1_SPEED_PIN, G1_DIR_PIN);
Motor gearbox_right(G2_SPEED_PIN, G2_DIR_PIN);

Driver driver(&front_left, &front_right, &back_left, &back_right);

Ping ping_sensor_center(PING_CENTER_TRIG_PIN, PING_CENTER_ECHO_PIN);
Ping ping_sensor_left(PING_LEFT_TRIG_PIN, PING_LEFT_ECHO_PIN);
Ping ping_sensor_right(PING_RIGHT_TRIG_PIN, PING_RIGHT_ECHO_PIN);

Scooper arms(&actuator_left, &actuator_right, &gearbox_left, &gearbox_right, LIMIT_SWITCH_LEFT, LIMIT_SWITCH_RIGHT);

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

void ping_func(char* tokens[], size_t token_count)
{
	switch(atoi(tokens[1])) {
		case 0:
			Serial.println(ping_sensor_center.getCentimeters(), DEC);
			break;

		case 1:
			Serial.println(ping_sensor_left.getCentimeters(), DEC);
			break;

		case 2:
			Serial.println(ping_sensor_right.getCentimeters(), DEC);
			break;
	}
}

void scoop_func(char* tokens[], size_t token_count)
{
	arms.scoop();
	Serial.println("scooped");
}

void scoopcal_func(char* tokens[], size_t token_count)
{
	arms.calibrate();
	Serial.println("calibrated");
}

void setup()
{
	//sch.registerCommand("test", &test_func);
	sch.registerCommand("drive", &drive_func);
	sch.registerCommand("rotate", &rotate_func);
	sch.registerCommand("speed", &speed_func);
	sch.registerCommand("stop", &stop_func);
	sch.registerCommand("ping", &ping_func);
	sch.registerCommand("scoop", &scoop_func);
	sch.registerCommand("scoop_calibrate", &scoopcal_func);

	sch.init();
	driver.init();
	ping_sensor_center.init();
	ping_sensor_left.init();
	ping_sensor_right.init();
	arms.init();
}

void loop() {}

void serialEvent()
{
	sch.handleCommand();
}
