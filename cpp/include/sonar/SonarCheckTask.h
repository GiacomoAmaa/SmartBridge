#ifndef __SONAR_TASK__
#define __SONAR_TASK__

#include "Sonar.h"
#include "../scheduler/Task.h"
#include "../utility/AlarmState.h"
#include "../utility/BaseView.h"

//#define MAX_WATER_LEVEL 2
//#define MIN_WATER_LEVEL 400
#define WATER_LEVEL_ALARM 10.0
#define WATER_LEVEL_PREALARM 20.0

#define NORMAL_PERIOD 50
#define PREALARM_PERIOD 30
#define ALARM_PERIOD 15

class SonarCheckTask : public Task{
    AlarmState* currState = nullptr;
    Sonar* sonar = nullptr;
    int currWaterLevel = 0;

    void updateWaterLevel(float distance) {
        if (distance >= WATER_LEVEL_PREALARM && distance < WATER_LEVEL_ALARM) {
            currWaterLevel = 1;
            return;
        }
        if (distance >= WATER_LEVEL_ALARM) {
            currWaterLevel = 2;
            return;
        }
        currWaterLevel = 0;
    }

    public:
        SonarCheckTask(AlarmState* currState, Sonar* sonar);
        void init();
        void tick();
};

#endif