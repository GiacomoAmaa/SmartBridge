#include "ServoControlTask.h"
#include "Servo.h"

ServoControlTask::ServoControlTask(AlarmState* currState, int pin) {
    this->currState=currState;
    this->currControl=AUTO;
    this->pin=pin;
    this->servoM=new Servo();
}

void ServoControlTask::angle(int angle) {
    BaseView::printLog("angle: "+String(angle));
    if (angle < VALVE_MIN || angle > VALVE_MAX || currAngle == angle) {
        return;
    }
    currAngle = angle;
    setServoPosition(angle);
}

void ServoControlTask::init(int period, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot, LCDTask* lcd) {
    Task::init(period);
    this->sonar=sonar;
    this->inputBtn=inputBtn;
    this->pot=pot;
    this->lcd=lcd;
    angle(currAngle);
    BaseView::printLog("Servo initialization complete");
}

void ServoControlTask::tick() {
    if (*currState == ALARM) {
        String mode = "AUTO";
        switch(currControl){
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
        BaseView::printLog("Valve control mode: " + mode);
        lcd->appendMsg("Valve: " + String(currAngle) + "degrees");
    } else {
        currControl = AUTO;
        angle(VALVE_MIN);
    }
}