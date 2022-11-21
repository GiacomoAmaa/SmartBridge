#ifndef __BUTTON__
#define __BUTTON__

#include "utility/BaseView.h"

class Button : public BaseView {
    int pin;

    public: 
        Button(int pin);
        bool isPressed();
};

#endif