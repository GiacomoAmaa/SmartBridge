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
}

void SonarCheckTask::tick() {
    float check = sonar->calculateDistance(SonarView::measure(sonar->getTrigPin(), sonar->getEchoPin()));
    updateWaterLevel(check);
    switch(currWaterLevel) {
        case 1:
            *currState = PREALARM;
            Task::setPeriod(PREALARM_PERIOD);
            sprintf(message, "Water: %.1fcm", currDistance);
            display->print(message);
            break;
        case 2:
            *currState = ALARM;
            Task::setPeriod(ALARM_PERIOD);
            sprintf(message, "Water: %.1fcm", currDistance);
            display->print(message);
            break;
        default:
            char msg = ' ';
            *currState = NORMAL;
            Task::setPeriod(NORMAL_PERIOD);
            display->print(&msg);
            break;
    }
}