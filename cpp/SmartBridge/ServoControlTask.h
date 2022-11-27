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

class ServoControlTask : public Task {
    AlarmState* currState = nullptr;
    SonarCheckTask* sonar = nullptr;
    Potentiometer* pot = nullptr;
    Servo* servoM = nullptr;
    Button* inputBtn = nullptr;
    bool userControlled = false;
    int currAngle = 0;
    int pin;

    void setServoPosition(int angle) {
        servoM->attach(pin);
        servoM->write(angle);
        servoM->detach();
    }

    int angleFromRotation(int rotation) {
        return VALVE_MAX * rotation / POT_MAX_VALUE;
    }

    int angleFromWaterLvl(int waterLevel) {
        return VALVE_MAX * waterLevel /* WATER_LEVEL_MAX*/;
    }

    public:
        ServoControlTask(AlarmState* currState, int pin);
        void angle(int angle);
        void init(int period, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot);
        void tick();
};

#endif