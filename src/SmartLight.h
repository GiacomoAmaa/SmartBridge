#ifndef __SMARTLIGHT__
#define __SMARTLIGHT__

#include "Light.h"

class SmartLight: public Light { 
public:
  SmartLight(int pin);
  void switchOn();
  void switchOff();    
private:
  int pin;  
};

#endif