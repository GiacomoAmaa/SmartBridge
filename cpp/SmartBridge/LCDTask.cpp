#include "LCDTask.h"
#include "BaseView.h"

LCDTask::LCDTask() {
    view = new LCDView();
}

void LCDTask::init(int period) {
    Task::init(period);
    view->init(MAX_COLS, MAX_ROWS);
    view->clean();
    BaseView::printLog("LCD initialization complete");
}

void LCDTask::appendMsg(String msg) {
    lines[currRow] = msg;
    currRow++;
}

void LCDTask::tick() {
    view->clean();
    for (int i=0; i<currRow; i++){
      view->printScreen(i, lines[i]);
    }
    currRow = 0;
}