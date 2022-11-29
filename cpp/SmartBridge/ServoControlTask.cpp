#include "ServoControlTask.h"
#include "Servo.h"

ServoControlTask::ServoControlTask(AlarmState* currState, int pin) {
    this->currState=currState;
    this->currControl=AUTO;
    this->pin=pin;
    this->servoM=new Servo();
}

void ServoControlTask::angle(int angle) {
    #ifdef DEBUG
    BaseView::printLog("angle: "+String(angle));
    #endif
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
    #ifdef DEBUG
    BaseView::printLog("Servo initialization complete");
    #endif
}

void ServoControlTask::tick() {
    if (*currState == ALARM) {
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
            angle(angleFromWaterLvl(sonar->getCurrentHeightLvl()));
            buttonSetMode(MANUAL);
            break;
        }
        #ifdef DEBUG
        BaseView::printLog("Valve control mode: " + mode);
        #endif
        lcd->appendMsg("Valve: " + String(currAngle) + "degrees");
    } else {
        currControl = AUTO;
        angle(VALVE_MIN);
    }
}

int ServoControlTask::getCurrValveOpening() {
  return map(currAngle, VALVE_MIN, VALVE_MAX, 0, 100);
}

String ServoControlTask::getValveControl(){
  return mode;
}

void ServoControlTask::setValveControl(ServoControl crtl){
  currControl = crtl;
}
