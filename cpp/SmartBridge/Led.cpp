#include "Led.h"

Led::Led(int pin){
  this->pin = pin;
  this->state = OFF;
}

bool Led::isOn() {
  return state == ON;
}

bool Led::isOff() {
  return state == OFF;
}

int Led::getPin() {
  return pin;
}

void Led::turnOn() {
  state = ON;
}

void Led::turnOff() {
  state = OFF;
}
