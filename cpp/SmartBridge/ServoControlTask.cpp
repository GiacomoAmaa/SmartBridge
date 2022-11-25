#include "ServoControlTask.h"
#include "Servo.h"

bool btnHold = false;

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
    BaseView::printLog("Servo initialization complete");
}

void ServoControlTask::tick() {
    if (*currState == ALARM) {
        if (inputBtn->isPressed() && !btnHold)  {
            btnHold = true;
            userControlled = userControlled ? false : true;
            String msg = "Manual valve control ";
            msg = userControlled ? msg+"enabled" : msg+"disabled";
            BaseView::printLog(msg);
        } else {
            btnHold = false;
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