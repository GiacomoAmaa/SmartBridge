#include "LCDTask.h"
#include "BaseView.h"

LCDTask::LCDTask(AlarmState* currState) {
  view = new LCDView();
  this->currState = currState;
  this->prevState = *currState;
}

void LCDTask::init(int period) {
  Task::init(period);
  view->init();
  view->clean();
  BaseView::printLog("LCD initialization complete");
}

void LCDTask::appendMsg(String msg) {
  lines[currRow] = msg;
  currRow++;
}

void LCDTask::tick() {
  switch(currState) {
    case PREALARM:
      if(stateChanged()){
        prevState = *currState;
        view->clean()
        view->printLayout(0,"PREALARM");
        view->printLayout(1, "WL: ");
      }
      break;
    case ALARM:
      if(stateChanged()){
        prevState = *currState;
        view->clean();
        view->printLayout(0,"ALARM");
        view->printLayout(1, "VO: ");
      }
      break;
    default:
      if(stateChanged()){
        prevState = *currState;
        view->clean();
      }
      break;
  }
  view->clean();
  for (int i=0; i<currRow; i++){
    BaseView::printLog("LCD Line " + String(i) + ": " + lines[i]);
    view->printScreen(i, lines[i]);
  }
  currRow = 0;
}
