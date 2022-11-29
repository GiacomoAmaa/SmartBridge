#ifndef __LIGHT_VIEW__
#define __LIGHT_VIEW__

#include "BaseView.h"

class LightSensorView : public BaseView {
  public:
    static int measure(int pin) {
      return analogRead(pin);
    }
};

#endif