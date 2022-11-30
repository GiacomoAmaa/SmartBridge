#ifndef __VIEW__
#define __VIEW__

#include "Arduino.h"
#include "Config.h"

typedef enum{OUT, IN} Mode;

class BaseView {
  public:
    /**
    * Sets up the given pin to either I or O
    */
    static void setupPin(int pin, Mode mode) {
      if (mode == IN) {
        pinMode(pin, INPUT);
      }
      if (mode == OUT) {
        pinMode(pin, OUTPUT);
      }
    }
    /**
    * Prints the given message if the debug sign is defined
    */
    static void printLog(String message) {
      #ifdef DEBUG
        Serial.println(message);
      #endif
    }
};

#endif