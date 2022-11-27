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
        String mode = "AUTO";
        switch(*currControl){
          case MANUAL: 
            angle(angleFromRotation(pot->getRotation()));
            buttonSetMode(AUTO);
            mode = "MANUAL";
            break;
          case REMOTE:
            mode = "REMOTE";
            break;
          default:
            angle(angleFromWaterLvl(sonar->getCurrentWaterDist()));
            buttonSetMode(MANUAL);
            break;
        }
        BaseView::printlog("Valve control mode: " + mode);
    } else {
        userControlled = false;
        angle(VALVE_MIN);
    }
}