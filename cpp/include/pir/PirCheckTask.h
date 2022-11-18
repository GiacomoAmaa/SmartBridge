#ifndef __PIR_TASK__
#define __PIR_TASK__

#include "scheduler/Task.h"
#include "utility/AlarmState.h"

class PirCheckTask : public Task {
    AlarmState* currState = nullptr;
    bool detected = false;
    int pirPin;

    public:
        PirCheckTask(AlarmState* currState, int pirPin);
        bool movementDetected();
        void init(int period);
        void tick();
};

#endif