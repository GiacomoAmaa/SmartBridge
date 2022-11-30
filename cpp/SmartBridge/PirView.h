#ifndef __PIR_VIEW__
#define __PIR_VIEW__

#include "Arduino.h"
#include "BaseView.h"

class PirView : public BaseView {
  public:
    /**
    * Calibrates the sensors taking ambient samples
    */
    static void calibrate(int time){
      const int max_line_space = 10;
      #ifdef DEBUG
        Serial.print("Calibrating PIR...");
      #endif
      for (int i=0; i<time; i++) {
        if (i < max_line_space) {
          #ifdef DEBUG
            Serial.print(".");
          #endif
        }
        delay(1000);
      }
      #ifdef DEBUG
        Serial.println(" done");
      #endif
    }

    /**
    * Reads the value from the pir's pin
    */
    static bool checkMovement(int pin) {
      return digitalRead(pin) == HIGH;
    }
};

#endif