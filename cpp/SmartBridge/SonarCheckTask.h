#ifndef __SONAR_TASK__
#define __SONAR_TASK__

#include "Sonar.h"
#include "Task.h"
#include "LCDTask.h"
#include "AlarmState.h"
#include "BaseView.h"

#define WATER_LEVEL_MAX 100
#define WATER_LEVEL_ALARM 95
#define WATER_LEVEL_PREALARM 40
#define WATER_LEVEL_MIN 0

#define PREALARM_PERIOD 15
#define ALARM_PERIOD 25

class SonarCheckTask : public Task{
    AlarmState* currState = nullptr;
    Sonar* sonar = nullptr;
    LCDTask* display = nullptr;
    int currDistance = 0;
    int currHeightLvl = 0;
    int currWaterLevel = 0;
    int alarm;
    int prealarm;
    int normal;

    void updateWaterLevel(int distance) {
        currDistance = distance;
        currHeightLvl = map(distance, MIN_DISTANCE, MAX_DISTANCE, WATER_LEVEL_MAX, WATER_LEVEL_MIN);
        BaseView::printLog("Water distance: " + String(currDistance) + " cm");
        if (currHeightLvl >= WATER_LEVEL_PREALARM && currHeightLvl < WATER_LEVEL_ALARM) {
            currWaterLevel = 1;
            return;
        }
        if (currHeightLvl >= WATER_LEVEL_ALARM) {
            currWaterLevel = 2;
            return;
        }
        currWaterLevel = 0;
    }

    public:
        SonarCheckTask(AlarmState* currState, int trigPin, int echoPin);
        double getCurrentWaterDist();
        void init(int period, LCDTask* display);
        void tick();
};

#endif