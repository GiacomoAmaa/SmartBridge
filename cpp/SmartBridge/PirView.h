#ifndef __PIR_VIEW__
#define __PIR_VIEW__

#include "Arduino.h"
#include "BaseView.h"

class PirView : public BaseView {
    public:
        static void calibrate(int time){
            const int max_line_space = 10; 
            Serial.print("Calibrating PIR...");
            for (int i=0; i<time; i++) {
                if (i < max_line_space) {
                    Serial.print(".");
                }
                delay(1000);
            }
            Serial.println(" done");
        }

        static bool checkMovement(int pin) {
            return digitalRead(pin) == HIGH;
        }
};

#endif