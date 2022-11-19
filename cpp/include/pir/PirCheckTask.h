#ifndef __PIR_TASK__
#define __PIR_TASK__

#include "scheduler/Task.h"
#include "utility/AlarmState.h"

#define CALIBRATION_TIME 10

class PirCheckTask : public Task {
    bool detected = false;
    int pirPin;

    public:
        PirCheckTask(int pirPin);
        bool isMovementDetected();
        void init(int period);
        void tick();
};

#endif