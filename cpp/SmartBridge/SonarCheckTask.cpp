#include "SonarCheckTask.h"
#include "Sonar.h"
#include "SonarView.h"

SonarCheckTask::SonarCheckTask(AlarmState* currState, int trigPin, int echoPin) {
  this->currState=currState;
  this->sonar=new Sonar(trigPin, echoPin);
}

double SonarCheckTask::getCurrentWaterDist() {
  return currDistance;
}

int SonarCheckTask::getCurrentHeightLvl() {
  return currHeightLvl;
}

void SonarCheckTask::init(int period, LCDTask* display) {
  Task::init(period);
  this->display=display;
  normal = period;
  prealarm = normal - PREALARM_PERIOD;
  alarm = normal - ALARM_PERIOD;

  SonarView::setupPin(sonar->getTrigPin(), sonar->getEchoPin());
  #ifdef DEBUG
    BaseView::printLog("Sonar initialization complete");
  #endif
}

void SonarCheckTask::tick() {
  int check = sonar->calculateDistance(SonarView::measure(sonar->getTrigPin(), sonar->getEchoPin()));
  updateWaterLevel(check);
  switch(currWaterLevel) {
    case 1:
      if (*currState != PREALARM) {
        #ifdef DEBUG
          BaseView::printLog("Alarm state changed to PREALARM");
        #endif
        Task::setPeriod(prealarm);
      }
      *currState = PREALARM;
      display->appendMsg("Water: "+String(currDistance)+"cm");
      break;
    case 2:
      if (*currState != ALARM) {
        #ifdef DEBUG
          BaseView::printLog("Alarm state changed to ALARM");
        #endif
        Task::setPeriod(alarm);
      }
      *currState = ALARM;
      display->appendMsg("Water: "+String(currDistance)+"cm");
      break;
    default:
      if (*currState != NORMAL) {
        #ifdef DEBUG
          BaseView::printLog("Alarm state changed to NORMAL");
        #endif
        Task::setPeriod(normal);
      }
      *currState = NORMAL;
      break;
  }
}