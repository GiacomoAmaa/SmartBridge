#ifndef __POTENTIOMETER_VIEW__
#define __POTENTIOMETER_VIEW__

#include "utility/BaseView.h"
#include "Arduino.h"

class PotentiometerView : public BaseView {
    public:
        static int checkRotation(int pin) {
            return analogRead(pin);
        }
};

#endif