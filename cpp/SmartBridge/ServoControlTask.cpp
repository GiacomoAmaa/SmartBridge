#include "ServoControlTask.h"
#include "Servo.h"

ServoControlTask::ServoControlTask(AlarmState* currState, int pin, ServoControl* currControl) {
    this->currState=currState;
    this->currControl=currControl;
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
        switch(*currControl){
          
          case AUTO: angle(angleFromWaterLvl(sonar->getCurrentWaterDist()));
            changeControl(MANUAL);
            break;
          case MANUAL: angle(angleFromRotation(pot->getRotation()));
            chengeControl(AUTO);
            break;
          case REMOTE

        }
    } else {
        userControlled = false;
        angle(VALVE_MIN);
    }
}