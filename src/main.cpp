#include <Arduino.h>

#include "variables.h"
#include "led_control.h"
#include "motor_control.h"
#include "remote_control.h"

void setup()
{
	Serial.begin(115200);

	LedControl::begin();
	MotorControl::begin();
	RemoteControl::begin();
}

void loop()
{
	LedControl::handle();
	MotorControl::handle();
	RemoteControl::handle();
}