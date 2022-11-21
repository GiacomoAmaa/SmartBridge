#include "servo/ServoView.h"

ServoView::ServoView(int pin){
    this->pin=pin;
}

void ServoView::setPosition(int angle){
    motor.attach(pin);
    motor.write(angle);
    motor.detach();
}