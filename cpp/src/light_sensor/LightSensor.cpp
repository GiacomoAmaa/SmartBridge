#include "light_sensor/LightSensor.h"

LightSensor::LightSensor(int pin) {
    this->pin=pin;
}

int LightSensor::getPin() {
    return pin;
}

double LightSensor::calculateVoltage(int rawVal) {
    return (double) rawVal * 5/1024;
}