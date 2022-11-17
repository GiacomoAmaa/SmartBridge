#ifndef __VIEW__
#define __VIEW__

#include "Arduino.h"

typedef enum{OUT, IN} Mode;

class BaseView {
    public:
        static void setupPin(int pin, Mode mode) {
            if (mode == IN) {
                pinMode(pin, INPUT);
            }
            if (mode == OUT) {
                pinMode(pin, OUTPUT);
            }
        }
};

#endif