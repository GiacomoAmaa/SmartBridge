#include "sonar/SonarCheckTask.h"
#include "sonar/Sonar.h"
#include "sonar/SonarView.h"

SonarCheckTask::SonarCheckTask(AlarmState* currState, Sonar* sonar) {
    this->currState=currState;
    this->sonar=sonar;
}

int SonarCheckTask::getCurrentWaterLvl() {
    return currWaterLevel;
}

void SonarCheckTask::init() {
    Task::init(NORMAL_PERIOD);
    SonarView::setupPin(sonar->getTrigPin(), sonar->getEchoPin());
}

void SonarCheckTask::tick() {
    float check = sonar->calculateDistance(SonarView::measure(sonar->getTrigPin(), sonar->getEchoPin()));
    updateWaterLevel(check);
    switch(currWaterLevel) {
        case 1:
            *currState = PREALARM;
            Task::setPeriod(PREALARM_PERIOD);
            break;
        case 2:
            *currState = ALARM;
            Task::setPeriod(ALARM_PERIOD);
            break;
        default:
            *currState = NORMAL;
            Task::setPeriod(NORMAL_PERIOD);
            break;
    }
}