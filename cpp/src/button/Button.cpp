#include "button/Button.h"
#include "Arduino.h"

Button::Button(int pin) {
    this->pin=pin;
    BaseView::setupPin(pin, IN);
}

bool Button::isPressed() {
    return digitalRead(pin);
}