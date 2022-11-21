#ifndef __SERVO_VIEW__
#define __SERVO_VIEW__

#include <Servo.h>

class ServoView {
    Servo motor;
    int pin;

    public:
        ServoView(int pin);
        void setPosition(int angle);
};

#endif