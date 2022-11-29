#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "LCDView.h"
#include "Task.h"

class LCDTask : public Task {
  LCDView* view = nullptr;
  String lines[MAX_ROWS];
  int currRow = 0;
  AlarmState* currState = nullptr;
  AlarmState prevState = null;

  bool stateChanged(){
    return *currState == prevState;
  }

  public:
    LCDTask(AlarmState* currState);
    void init(int period);
    void tick();
};

#endif