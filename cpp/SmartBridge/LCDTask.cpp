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
  switch(*currState) {
    case PREALARM:
      if(stateChanged()){
        prevState = *currState;
        view->clean();
        view->printLayout(0, 0, "PREALARM");
        view->printLayout(0, 1, "Water:    cm");
      }
      view->printLayout(7, 1, lines[0]);
      break;
    case ALARM:
      if(stateChanged()){
        prevState = *currState;
        view->clean();
        view->printLayout(0, 0, "ALARM");
        view->printLayout(0, 1, "WL:   cm VOP:");
      }
      view->printLayout(3, 1, lines[0] + " ");
      view->printLayout(MAX_COLS - 3, 1, lines[1] + "  ");
      break; 
    default:
      if(stateChanged()){
        prevState = *currState;
        view->clean();
      }
      break;
  }
  currRow = 0;
}
