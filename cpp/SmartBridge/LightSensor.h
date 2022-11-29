#ifndef __LIGHT_SENSOR__
#define __LIGHT_SENSOR__

#include <Arduino.h>

#define MIN_LIGHT_VALUE 0
#define MAX_LIGHT_VALUE 1000

class LightSensor {
  int pin;

  public:
    LightSensor(int pin);
    /**
    * returns the pin of the light sensor
    */
    int getPin();
    /**
    * Calculates the light level from the analog input value
    */
    int calculateLightLevel(int rawVal);
};

#endif