#ifndef __BUTTON_VIEW__
#define __BUTTON_VIEW__

#include "BaseView.h"
#include "Arduino.h"

class ButtonView : public BaseView {
    public:
        static bool checkPress(int pin){
            return digitalRead(pin);
        }
};

#endif