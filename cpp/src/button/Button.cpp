#include "button/Button.h"
#include "button/ButtonView.h"

Button::Button(int pin) {
    this->pin=pin;
}

void Button::init() {
    BaseView::setupPin(pin, IN);
}

bool Button::isPressed() {
    return ButtonView::checkPress(pin);
}