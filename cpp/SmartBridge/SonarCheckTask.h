#ifndef __SONAR_TASK__
#define __SONAR_TASK__

#include "Sonar.h"
#include "Task.h"
#include "LCD.h"
#include "AlarmState.h"
#include "BaseView.h"

#define MAX_WATER_LEVEL 2
#define MIN_WATER_LEVEL 400
#define WATER_LEVEL_MAX 0
#define WATER_LEVEL_ALARM 30
#define WATER_LEVEL_PREALARM 60

#define PREALARM_PERIOD 15
#define ALARM_PERIOD 25

#define MESSAGE_LENGTH 20

class SonarCheckTask : public Task{
    AlarmState* currState = nullptr;
    Sonar* sonar = nullptr;
    LCD* display = nullptr;
    int currDistance = 0;
    int currWaterLevel = 0;
    int alarm;
    int prealarm;
    int normal;

    void updateWaterLevel(double distance) {
        currDistance = (int)(distance * 100);
        currDistance = map(currDistance, MIN_WATER_LEVEL, MAX_WATER_LEVEL, 0, 100);
        BaseView::printLog("Water distance: " + String(currDistance));
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
        SonarCheckTask(AlarmState* currState, int trigPin, int echoPin);
        double getCurrentWaterDist();
        void init(int period, LCD* display);
        void tick();
};

#endif