#ifndef __LED_VIEW__
#define __LED_VIEW__

#include "BaseView.h"

class LedView : public BaseView{
  public:
    static void setLedState(int pin, LedState state) {
      if (state == ON) {
        digitalWrite(pin, HIGH);
        return;
      }
      digitalWrite(pin, LOW);
    }
};

#endif