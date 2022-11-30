#include "LCDTask.h"
#include "BaseView.h"

LCDTask::LCDTask(AlarmState* currState) {
  view = new LCDView();
  this->currState = currState;
  this->prevState = *currState;
}

void LCDTask::init(int period, ServoControlTask* servo, SonarCheckTask* sonar) {
  Task::init(period);
  view->init();
  view->clean();
  this->sonar = sonar;
  this->servo = servo;
  BaseView::printLog("LCD initialization complete");
}

void LCDTask::tick() {
  if(stateChanged()){
    view->clean();
  }
  switch(*currState) {
    case PREALARM:
      view->printLayout(0,"PREALARM");
      view->printLayout(1,"WaterLvl:" + String((int)sonar->getCurrentWaterDist()) + "cm ");
      break;
    case ALARM:
      view->printLayout(0, "ALARM");
      view->printLayout(1,"WL:" + String((int)sonar->getCurrentWaterDist()) + "cm " 
        + "VO:" + String(map(servo->getCurrValveOpening(), 0, 100, VALVE_MIN, VALVE_MAX)) + "  ");
      break; 
    default:
      view->clean();
      break;
  }
}
