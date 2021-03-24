#pragma once

// ----- Static Controller Settings -----

// Settings for led_control.h
#define RGB_LED_PIN 12
#define LED_DIM_DELAY 10000
#define LED_DIM_SPEED 5000 // Dim led in 5 seconds


// Settings for motor_control.h
#define STEP_PIN 2
#define DIR_PIN 3
#define ENABLE_PIN 4
#define MICRO_PIN_1 5
#define MICRO_PIN_2 6
#define MICRO_PIN_3 7
#define OPEN_ENDSTOP_PIN 8
#define CLOSE_ENDSTOP_PIN 9

#define MAX_MOTOR_SPEED 10000
#define MOTOR_SPEED 9500
#define AUTO_CLOSE_ON_STARTUP 1
#define MOTOR_RUN_TIMEOUT 15000 // Motor should not run for more than 15 seconds

// Settings for remote_control.h
#define MANUAL_OPEN_BUTTON 10
#define MANUAL_CLOSE_BUTTON 11

// ----- END Static Controller Settings -----


// ----- Global Objects -----
#include <AccelStepper.h>
AccelStepper stepper;

#include <Bounce2.h>
Bounce openDebouncer;
Bounce closeDebouncer;

#include <FastLED.h>
// ----- END Global Objects -----