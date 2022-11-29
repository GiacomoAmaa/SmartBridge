#include "LCDTask.h"
#include "BaseView.h"

LCDTask::LCDTask() {
  view = new LCDView();
}

void LCDTask::init(int period) {
  Task::init(period);
  view->init();
  view->clean();
  #ifdef DEBUG
    BaseView::printLog("LCD initialization complete");
  #endif
}

void LCDTask::appendMsg(String msg) {
  lines[currCol] = msg;
  currCol++;
}

void LCDTask::tick() {
  view->clean();
  for (int i=0; i<currCol; i++){
    view->printScreen(i, lines[i]);
  }
  currCol = 0;
}
