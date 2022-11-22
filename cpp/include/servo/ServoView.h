#ifndef __SERVO_VIEW__
#define __SERVO_VIEW__

#include <Servo.h>

class ServoView {
    Servo motor;

    public:
        void setPosition(int pin, int angle);
};

#endif