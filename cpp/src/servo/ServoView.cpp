#include "servo/ServoView.h"

void ServoView::setPosition(int pin, int angle){
    motor.attach(pin);
    motor.write(angle);
    motor.detach();
}