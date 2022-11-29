#include "Potentiometer.h"
#include "PotentiometerView.h"

Potentiometer::Potentiometer(int pin) {
  this->pin=pin;
}

int Potentiometer::getRotation() {
  return PotentiometerView::checkRotation(pin);
}