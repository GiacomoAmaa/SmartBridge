#include "potentiometer/Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) {
    this->pin=pin;
}

int Potentiometer::getRotation() {
    return analogRead(pin);
}