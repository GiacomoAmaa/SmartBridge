#ifndef __LIGHT_SENSOR__
#define __LIGHT_SENSOR__

#include <Arduino.h>

class LightSensor {
    int pin;

    public:
        LightSensor(int pin);
        int getPin();
        int calculateLightLevel(int rawVal);
};

#endif