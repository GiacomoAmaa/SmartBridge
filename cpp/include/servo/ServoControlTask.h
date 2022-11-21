#ifndef __SERVO_TASK__
#define __SERVO_TASK__

#include "ServoView.h"
#include "scheduler/Task.h"
#include "utility/AlarmState.h"
#include "sonar/SonarCheckTask.h"
#include "button/Button.h"
#include "potentiometer/Potentiometer.h"

#define VALVE_MIN 0
#define VALVE_MAX 180

class ServoControlTask : public Task {
    AlarmState* currState = nullptr;
    SonarCheckTask* sonar = nullptr;
    Potentiometer* pot = nullptr;
    ServoView* servoM = nullptr;
    Button* inputBtn = nullptr;
    bool userControlled = false;
    int currAngle = 0;

    int angleFromRotation(int rotation) {
        return VALVE_MAX * rotation / POT_MAX_VALUE;
    }

    int angleFromWaterLvl(int waterLevel) {
        return VALVE_MAX * waterLevel / WATER_LEVEL_MAX;
    }

    public:
        ServoControlTask(AlarmState* currState, ServoView* servoM, SonarCheckTask* sonar, Button* inputBtn, Potentiometer* pot);
        void angle(int angle);
        void init(int period);
        void tick();
};

#endif