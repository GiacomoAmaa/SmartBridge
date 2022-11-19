#ifndef __LED_VIEW__
#define __LED_VIEW__

#include "utility/BaseView.h"

class LedView : public BaseView{
    public:
        static void setLedState(int pin, LedState state) {
            if (state == ON) {
                digitalWrite(pin, LOW);
                return;
            }
            digitalWrite(pin, HIGH);
        }
};

#endif