#ifndef __PIR_VIEW__
#define __PIR_VIEW__

#include "Arduino.h"
#include "utility/BaseView.h"

class PirView : public BaseView {
    public:
        static bool checkMovement(int pin) {
            return digitalRead(pin) == HIGH;
        }
};

#endif