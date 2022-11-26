#include "LightSensor.h"

LightSensor::LightSensor(int pin) {
    this->pin=pin;
}

int LightSensor::getPin() {
    return pin;
}

int LightSensor::calculateLightLevel(int rawVal) {
    return map(rawVal,0,1000,0,100);
}