#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "LCDView.h"
#include "Task.h"
#include "AlarmState.h"

class LCDTask : public Task {
  LCDView* view = nullptr;
  String lines[MAX_ROWS];
  int currRow = 0;
  AlarmState* currState = nullptr;
  AlarmState prevState;

  bool stateChanged(){
    return *currState == prevState;
  }

  public:
    LCDTask(AlarmState* currState);
    void appendMsg(String msg);
    void init(int period);
    void tick();
};

#endif