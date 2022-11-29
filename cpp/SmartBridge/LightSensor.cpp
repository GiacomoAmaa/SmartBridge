#include "LightSensor.h"

LightSensor::LightSensor(int pin) {
  this->pin=pin;
}

int LightSensor::getPin() {
  return pin;
}

int LightSensor::calculateLightLevel(int rawVal) {
  return map(rawVal,MIN_LIGHT_VALUE,MAX_LIGHT_VALUE,0,100);
}