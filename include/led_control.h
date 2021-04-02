#pragma once
#include "variables.h"

// Status color definitions
enum class StatusColors : uint8_t
{
    OPENING = 0,
    CLOSING = 1,
    HOMING = 2,
    RESTARTING = 3,
    ERROR = 4,
    OFF = 5,
    STANDBY = 6
};

// Error event definitions
enum class ErrorCode : uint8_t
{
    NONE = 0,
    MOTOR_ENDSTOP_ERROR = 1
};

class LedControl
{
private:
    static CRGB statusLedColor[1];

    // Led dimming state variables
    static bool enableLedDim;
    static bool tempLedDim;
    static bool requestLedDim;
    static bool ledDimmed;
    static unsigned long lastLEDWakeTime;
    static unsigned long lastLEDDimTime;

    // Error state variables
    static bool errorHasOccurred;
    static ErrorCode errorCode;

public:
    // Methods
    static void setStatusLedColor(CRGB newColor, bool dimLed = true);
    static void setStatusLedColor(StatusColors newColor, bool dimLed = true);
    static CRGB getStatusLedColor();
    static void setBaseStatus();

    static void setLedDimTemp(bool shouldDim);

    static void setErrorHasOccurred(bool hasErrorOccurred, ErrorCode newErrorCode = ErrorCode::NONE);
    static bool hasErrorOccurred();
    static ErrorCode getErrorCode();
    static String getErrorCodeString(ErrorCode errorCode);

    static void begin();
    static void handle();
};

// Static member definitions
CRGB LedControl::statusLedColor[1] = { CRGB::Black };
bool LedControl::enableLedDim = false;
bool LedControl::tempLedDim = false;
bool LedControl::requestLedDim = false;
bool LedControl::ledDimmed = false;
unsigned long LedControl::lastLEDWakeTime = 0U;
unsigned long LedControl::lastLEDDimTime = 0U;
bool LedControl::errorHasOccurred = false;
ErrorCode LedControl::errorCode = ErrorCode::NONE;


// Public methods
void LedControl::setStatusLedColor(CRGB newColor, bool dimLed)
{
    statusLedColor[0] = newColor;
    FastLED.setBrightness(255);
    FastLED.show();

    requestLedDim = false;
    ledDimmed = false;

    if (dimLed)
    {
        enableLedDim = true;
        lastLEDWakeTime = millis();
    }
    else
    {
        enableLedDim = false;
    }
}

void LedControl::setStatusLedColor(StatusColors newColor, bool dimLed)
{

    switch (newColor)
    {
    case StatusColors::OPENING:
        statusLedColor[0] = CRGB::Green;
        break;
    case StatusColors::CLOSING:
        statusLedColor[0] = CRGB::Yellow;
        break;
    case StatusColors::HOMING:
        statusLedColor[0] = CRGB::Orange;
        break;
    case StatusColors::RESTARTING:
        statusLedColor[0] = CRGB::GreenYellow;
        break;
    case StatusColors::ERROR:
        statusLedColor[0] = CRGB::Red;
        break;
    case StatusColors::OFF:
        statusLedColor[0] = CRGB::Black;
        break;
    case StatusColors::STANDBY:
        statusLedColor[0] = CRGB::Blue;
        break;
    default:
        break;
    }

    setStatusLedColor(statusLedColor[0], dimLed);
}

CRGB LedControl::getStatusLedColor()
{
    return statusLedColor[0];
}

void LedControl::setBaseStatus()
{
    if (errorHasOccurred)
    {
        setStatusLedColor(StatusColors::ERROR);
    }
    else
    {
        setStatusLedColor(StatusColors::STANDBY);
    }
}

void LedControl::setLedDimTemp(bool shouldDim)
{
    tempLedDim = shouldDim;
}

void LedControl::setErrorHasOccurred(bool hasErrorOccurred, ErrorCode newErrorCode)
{
    errorHasOccurred = hasErrorOccurred;

    errorCode = newErrorCode;
}

bool LedControl::hasErrorOccurred()
{
    return errorHasOccurred;
}

ErrorCode LedControl::getErrorCode()
{
    return errorCode;
}

String LedControl::getErrorCodeString(ErrorCode errorCode)
{
    switch (errorCode)
    {
    case ErrorCode::NONE:
        return String("NONE");
        break;

    case ErrorCode::MOTOR_ENDSTOP_ERROR:
        return String("MOTOR_ENDSTOP_ERROR");
        break;

    default:
        return String("UNKNOWN");
        break;
    }
}

void LedControl::begin()
{
    Serial.println("Setting up led control");

    // Init static variables
    enableLedDim = true;
    tempLedDim = true;
    requestLedDim = false;
    ledDimmed = false;

    errorHasOccurred = false;

    FastLED.addLeds<WS2812B, RGB_LED_PIN, GRB>(statusLedColor, 1);
    FastLED.setBrightness(255);
    setStatusLedColor(StatusColors::OFF);
    FastLED.show(); // Write data to led
}

void LedControl::handle()
{
    if (enableLedDim && tempLedDim)
    {
        // Handle led dim timeout
        if (!ledDimmed && !requestLedDim)
        {
            // Wait for timeout to dim led
            if (millis() - lastLEDWakeTime >= LED_DIM_DELAY)
            {
                requestLedDim = true;
                lastLEDDimTime = millis();
            }
        }
        else
        {
            if (!ledDimmed)
            {
                // Non-blocking led dimming
                unsigned long timeDifference = millis() - lastLEDDimTime;
                uint8_t calculatedVal = map(timeDifference, 0, LED_DIM_SPEED, 255, 1);

                FastLED.setBrightness(calculatedVal);
                FastLED.show();

                if (timeDifference >= LED_DIM_SPEED)
                {
                    // Led Dim complete
                    ledDimmed = true;
                    requestLedDim = false;
                    lastLEDDimTime = 0;
                }
            }
        }
    }
}