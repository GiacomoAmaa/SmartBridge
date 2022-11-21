#include "servo/ServoControlTask.h"
#include "servo/ServoView.h"

ServoControlTask::ServoControlTask(AlarmState* currState, ServoView* servoM, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot) {
    this->currState=currState;
    this->sonar=sonar;
    this->inputBtn=inputBtn;
    this->pot=pot;
    this->servoM=servoM;
}

void ServoControlTask::angle(int angle) {
    if (angle < VALVE_MIN || angle > VALVE_MAX) {
        return;
    }
    currAngle = angle;
    servoM->setPosition(angle);
}

void ServoControlTask::init(int period) {
    Task::init(period);
    angle(currAngle);
}

void ServoControlTask::tick() {
    if (*currState == ALARM) {
        if (inputBtn->isPressed()) {
            userControlled = true;
        }

        if (userControlled) {
            angle(angleFromRotation(pot->getRotation()));
        } else {
            angle(angleFromWaterLvl(sonar->getCurrentWaterLvl()));
        }
    } else {
        userControlled = false;
        angle(VALVE_MIN);
    }
}