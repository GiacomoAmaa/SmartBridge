#include "servo/ServoControlTask.h"
#include "servo/Servo.h"

ServoControlTask::ServoControlTask(AlarmState* currState, int pin) {
    this->currState=currState;
    this->pin=pin;
    this->servoM=new Servo();
}

void ServoControlTask::angle(int angle) {
    if (angle < VALVE_MIN || angle > VALVE_MAX) {
        return;
    }
    currAngle = angle;
    setServoPosition(angle);
}

void ServoControlTask::init(int period, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot) {
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
            angle(angleFromWaterLvl(sonar->getCurrentWaterDist()));
        }
    } else {
        userControlled = false;
        angle(VALVE_MIN);
    }
}