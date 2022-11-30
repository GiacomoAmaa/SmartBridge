#include "ServoControlTask.h"
#include "Servo.h"

ServoControlTask::ServoControlTask(AlarmState* currState, int pin) {
  this->currState=currState;
  this->currControl=AUTO;
  this->pin=pin;
  this->servoM=new Servo();
}

void ServoControlTask::init(int period, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot) {
  Task::init(period);
  this->sonar=sonar;
  this->inputBtn=inputBtn;
  this->pot=pot;
  angle(currAngle);
  BaseView::printLog("Servo initialization complete");
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

void ServoControlTask::setRemoteAngle(int angle) {
  remoteAngle = angle;
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
        angle(angleFromPercentage(remoteAngle));
        mode = "REMOTE";
        break;
      default:
        angle(angleFromWaterLvl(sonar->getCurrentHeightLvl()));
        buttonSetMode(MANUAL);
        mode = "AUTO";
        break;
    }
    BaseView::printLog("Valve control mode: " + mode);
  } else {
      currControl = AUTO;
      mode = "AUTO";
      angle(VALVE_MIN);
  }
}
