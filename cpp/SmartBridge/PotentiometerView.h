#ifndef __POTENTIOMETER_VIEW__
#define __POTENTIOMETER_VIEW__

#include "BaseView.h"
#include "Arduino.h"

class PotentiometerView : public BaseView {
  public:
    /**
    * Reads the analog input from the potentiometer
    */
    static int checkRotation(int pin) {
      return analogRead(pin);
    }
};

#endif