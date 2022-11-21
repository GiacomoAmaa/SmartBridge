#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include "utility/BaseView.h"

#define POT_MIN_VALUE 0
#define POT_MAX_VALUE 1024

class Potentiometer : public BaseView {
    int pin;

    public:
        Potentiometer(int pin);
        int getRotation();
};

#endif