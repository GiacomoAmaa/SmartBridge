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

void SonarCheckTask::init(LCD* display) {
    Task::init(NORMAL_PERIOD);
    this->display=display;
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
            sprintf(message, "Water: %.1fcm", currWaterLevel);
            display->print(message);
            break;
        case 2:
            *currState = ALARM;
            Task::setPeriod(ALARM_PERIOD);
            sprintf(message, "Water: %.1fcm", currWaterLevel);
            display->print(message);
            break;
        default:
            *currState = NORMAL;
            Task::setPeriod(NORMAL_PERIOD);
            sprintf(message, "");
            display->print(message);
            break;
    }
}