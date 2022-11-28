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
    Servo* servoM = nullptr;
    Button* inputBtn = nullptr;
    ServoControl currControl;
    bool btnHold = false;
    int currAngle = 0;
    int pin;

    void setServoPosition(int angle) {
        if (currAngle == angle) {
          return;
        }
        float coeff = (2250.0-750.0)/180;
        currAngle = angle;
        servoM->attach(pin);
        servoM->write(750 + angle*coeff);
        delay(DELAY_SERVO);
        servoM->detach();
        BaseView::printLog("Valve angle set to " + currAngle + " degrees"); 
    }

    int angleFromRotation(int rotation) {
        return map(rotation, POT_MIN_VALUE, POT_MAX_VALUE, VALVE_MIN, VALVE_MAX);
    }

    int angleFromWaterLvl(int waterLevel) {
        return map(waterLevel, WATER_LEVEL_ALARM, WATER_LEVEL_MAX, VALVE_MIN, VALVE_MAX);
    }

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
        void angle(int angle);
        void init(int period, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot);
        void tick();
};

#endif