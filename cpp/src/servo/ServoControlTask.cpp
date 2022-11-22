#include "servo/ServoControlTask.h"
#include "servo/ServoView.h"

ServoControlTask::ServoControlTask(AlarmState* currState, int pin) {
    this->currState=currState;
    this->pin=pin;
    this->servoM=new ServoView();
}

void ServoControlTask::angle(int angle) {
    if (angle < VALVE_MIN || angle > VALVE_MAX) {
        return;
    }
    currAngle = angle;
    servoM->setPosition(pin, angle);
}

void ServoControlTask::init(SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot, int period) {
    Task::init(period);
    this->sonar=sonar;
    this->inputBtn=inputBtn;
    this->pot=pot;
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