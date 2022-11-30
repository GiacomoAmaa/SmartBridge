#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "LCDView.h"
#include "Task.h"
#include "AlarmState.h"
#include "SonarCheckTask.h"
#include "ServoControlTask.h"

class LCDTask : public Task {
  LCDView* view = nullptr;
  AlarmState* currState = nullptr;
  ServoControlTask* servo = nullptr;
  SonarCheckTask* sonar = nullptr;

  AlarmState prevState;

  bool stateChanged(){
    return *currState != prevState;
  }

  public:
    LCDTask(AlarmState* currState);
    void init(int period, ServoControlTask* servo, SonarCheckTask* sonar);
    void tick();
};

#endif