#ifndef __SERIAL_COMMUNICATION_TASK__
#define __SERIAL_COMMUNICATION_TASK__

#include "Task.h"
#include "AlarmState.h"
#include "SonarCheckTask.h"
#include "LightCheckTask.h"
#include "LedPowerTask.h"
#include "ServoControlTask.h"
#include "SerialCommunication.h"


class SerialCommunicationTask : public Task {
    AlarmState* alertState = nullptr;
    SonarCheckTask* waterLvl = nullptr;
    ServoControlTask* valve = nullptr;
    LightCheckTask* luminosity = nullptr;
    LedPowerTask* light = nullptr;

    public:
        SerialCommunicationTask(AlarmState* currState, SonarCheckTask* waterLvl,
         ServoControlTask* valve, LightCheckTask* luminosity, LedPowerTask* light);

        void init();
        void tick();
};

#endif