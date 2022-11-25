#include "sonar/SonarCheckTask.h"
#include "sonar/Sonar.h"
#include "sonar/SonarView.h"

SonarCheckTask::SonarCheckTask(AlarmState* currState, int trigPin, int echoPin) {
    this->currState=currState;
    this->sonar=new Sonar(trigPin, echoPin);
}

double SonarCheckTask::getCurrentWaterDist() {
    return currDistance;
}

void SonarCheckTask::init(LCD* display) {
    Task::init(NORMAL_PERIOD);
    this->display=display;
    display->init();
    
    message = (char*)malloc(sizeof(char)*MESSAGE_LENGTH);
    SonarView::setupPin(sonar->getTrigPin(), sonar->getEchoPin());
    BaseView::printLog("Sonar initialization complete");
}

void SonarCheckTask::tick() {
    float check = sonar->calculateDistance(SonarView::measure(sonar->getTrigPin(), sonar->getEchoPin()));
    updateWaterLevel(check);
    switch(currWaterLevel) {
        case 1:
            if (*currState != PREALARM) {
                BaseView::printLog("Alarm state changed to PREALARM");
                Task::setPeriod(PREALARM_PERIOD);
            }
            *currState = PREALARM;
            sprintf(message, "Water: %.1f m", currDistance);
            display->print(message);
            break;
        case 2:
            if (*currState != ALARM) {
                BaseView::printLog("Alarm state changed to ALARM");
                Task::setPeriod(ALARM_PERIOD);
            }
            *currState = ALARM;
            sprintf(message, "Water: %.1f m", currDistance);
            display->print(message);
            break;
        default:
            if (*currState != NORMAL) {
                BaseView::printLog("Alarm state changed to NORMAL");
                Task::setPeriod(NORMAL_PERIOD);
            }
            char msg = ' ';
            *currState = NORMAL;
            display->print(&msg);
            break;
    }
}