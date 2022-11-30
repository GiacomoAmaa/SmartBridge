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

void SonarCheckTask::init(int period) {
  Task::init(period);
  normal = period;
  prealarm = normal - PREALARM_PERIOD;
  alarm = normal - ALARM_PERIOD;

  SonarView::setupPin(sonar->getTrigPin(), sonar->getEchoPin());
  BaseView::printLog("Sonar initialization complete");
}

void SonarCheckTask::tick() {
  int check = sonar->calculateDistance(SonarView::measure(sonar->getTrigPin(), sonar->getEchoPin()));
  updateWaterLevel(check);
  switch(currWaterLevel) {
    case 1:
      if (*currState != PREALARM) {
        BaseView::printLog("Alarm state changed to PREALARM");
        Task::setPeriod(prealarm);
      }
      *currState = PREALARM;
      break;
    case 2:
      if (*currState != ALARM) {
        BaseView::printLog("Alarm state changed to ALARM");
        Task::setPeriod(alarm);
      }
      *currState = ALARM;
      break;
    default:
      if (*currState != NORMAL) {
        BaseView::printLog("Alarm state changed to NORMAL");
        Task::setPeriod(normal);
      }
      *currState = NORMAL;
      break;
  }
}
