#ifndef __LED_VIEW__
#define __LED_VIEW__

#include "../utility/BaseView.h"

class LedView : public BaseView{
    public:
        static void setLedIntensity(int pin, int intensity) {
            if (intensity <= MIN_LED_INTENSITY) {
                digitalWrite(pin, LOW);
            } else if (intensity >= MAX_LED_INTENSITY) {
                digitalWrite(pin, HIGH);
            } else {
                analogWrite(pin, intensity);
            }
        }
};

#endif