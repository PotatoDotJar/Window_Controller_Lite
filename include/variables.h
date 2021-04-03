#pragma once

// ----- Static Controller Settings -----

// Settings for led_control.h
#define RGB_LED_PIN A1
#define LED_DIM_DELAY 10000
#define LED_DIM_SPEED 5000 // Dim led in 5 seconds


// Settings for motor_control.h
#define STEP_PIN 3
#define DIR_PIN 2
#define ENABLE_PIN 9
#define MICRO_PIN_1 8
#define MICRO_PIN_2 7
#define MICRO_PIN_3 6
#define OPEN_ENDSTOP_PIN 11
#define CLOSE_ENDSTOP_PIN 12

#define MAX_MOTOR_SPEED 10000
#define MOTOR_SPEED 9500
#define AUTO_CLOSE_ON_STARTUP 1
#define MOTOR_RUN_TIMEOUT 15000 // Motor should not run for more than 15 seconds

// Settings for remote_control.h
#define MANUAL_OPEN_BUTTON A4
#define MANUAL_CLOSE_BUTTON A5

// ----- END Static Controller Settings -----


// ----- Global Objects -----
#include <AccelStepper.h>
AccelStepper stepper;

#include <Bounce2.h>
Bounce openDebouncer;
Bounce closeDebouncer;

#include <FastLED.h>
// ----- END Global Objects -----