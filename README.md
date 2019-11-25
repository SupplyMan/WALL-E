# WALL-E Subsystem Board Firmware

This repo contains the firmware for a robot designed to collect trash which we are calling WALL-E. This system encapsulates some of the lower level functions of the robot, such as movement and sensor interaction, to make programming the higher level executive functions of the robot easier.

## Getting Started

### Prerequisites

The arduino IDE, and an appropriate board using an ATMEGA2560 microcontroller are required for compilation and use of this project. Follow the link below:

```
https://www.arduino.cc/en/main/software
```
### Using the System

To use this subsystem, the following structure must be followed when sending commands to the board.

```
Movement

	drive [speed (0-255)] [dir (0 = forward, 1 = strafe right, 2 = backward, 3 = strafe left)]
	rotate [speed (0-255)] [dir (0 = left, 1 = right)]
	speed [speed (0-255)]
	stop

Arm Control

	scoop (expected response = scooped)

Sensors

	ping (expected response = distance in cm)
```

All commands should be ended with a newline.

For example, to strafe left at half speed, one could use the following python code.

```
import serial
ser = serial.Serial('/dev/ttyUSB0')
ser.write(b'drive 127 3\n')
ser.close()
```

## Authors

* **Daniel Bloom** - [SupplyMan](https://github.com/SupplyMan)

## License

This project is licensed under the WTFPL License - see the [LICENSE.md](LICENSE.md) file for details
