#ifndef __PIRSENSORIMPL__
#define __PIRSENSORIMPL__

#include "PirSensor.h"
#include <Arduino.h>

#define CALIBRATION_TIME_SEC 3

class PirSensorImpl: public PirSensor {
 
public: 
  PirSensorImpl(int pin);
  bool detect();
  bool isDetected();

private:
  int pin;
  int detectedStatus;
  void calibrate();

};

#endif