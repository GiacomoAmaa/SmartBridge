#ifndef __SERVO_TASK__
#define __SERVO_TASK__

#include "Servo.h"
#include "Task.h"
#include "AlarmState.h"
#include "SonarCheckTask.h"
#include "Button.h"
#include "Potentiometer.h"

#define VALVE_MIN 0
#define VALVE_MAX 180

#define DELAY_SERVO 50

typedef enum {AUTO, MANUAL, REMOTE} ServoControl;

class ServoControlTask : public Task {
  AlarmState* currState = nullptr;
  SonarCheckTask* sonar = nullptr;
  Potentiometer* pot = nullptr;
  Button* inputBtn = nullptr;
  Servo* servoM = nullptr;
  ServoControl currControl;
  String mode = "AUTO";
  bool btnHold = false;
  int remoteAngle = 0;
  int currAngle = 0;
  int pin;

  /**
  * applies the given angle on the servo motor
  */
  void angle(int angle) {
    if (angle < VALVE_MIN || angle > VALVE_MAX || currAngle == angle) {
      return;
    }
    currAngle = angle;

    float coeff = (2250.0-750.0)/180;
    servoM->attach(pin);
    servoM->write(750 + angle*coeff);
    delay(DELAY_SERVO);
    servoM->detach();
    BaseView::printLog("Valve angle set to " + String(currAngle) + " degrees");
  }

  /**
  * calculates the opening angle of the valve from potentiometer input
  */
  int angleFromRotation(int rotation) {
    return map(rotation, POT_MIN_VALUE, POT_MAX_VALUE, VALVE_MIN, VALVE_MAX);
  }
  /**
  * calculates the opening angle of the valve from water level
  */
  int angleFromWaterLvl(int waterLevel) {
    return map(waterLevel, WATER_LEVEL_ALARM, WATER_LEVEL_MAX, VALVE_MIN, VALVE_MAX);
  }
  /**
  * calculates the opening angle of the valve from the JavaApp data
  */
  int angleFromPercentage(int percentage) {
    return map(percentage,0,100,VALVE_MIN,VALVE_MAX);
  }
  /**
  * checks the button for eventual switch to manual mode
  */
  void buttonSetMode(ServoControl crtl) {
    if (inputBtn->isPressed() && !btnHold)  {
      btnHold = true;
      currControl = crtl;
    } else if (!inputBtn->isPressed()){
      btnHold = false;
    }
  }

    public:
      ServoControlTask(AlarmState* currState, int pin);
      void init(int period, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot);
      /**
      * returns the current valve opening percentage
      */
      int getCurrValveOpening();
      /**
      * returns a string describing the current valve control
      */
      String getValveControl();
      /**
      * sets the valve control mode
      */
      void setValveControl(ServoControl crtl);
      /**
      * sets the remote angle to support remote control
      */
      void setRemoteAngle(int angle);
      void tick();
};

#endif