#ifndef __PIR_TASK__
#define __PIR_TASK__

#include "Task.h"
#include "AlarmState.h"

#define CALIBRATION_TIME 10

class PirCheckTask : public Task {
  bool detected = false;
  int pirPin;

  public:
    PirCheckTask(int pirPin);
    /**
    * Returns true if a moovement is detected
    */
    bool isMovementDetected();
    void init(int period);
    void tick();
};

#endif