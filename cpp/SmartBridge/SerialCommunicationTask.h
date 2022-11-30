#ifndef __SERIAL_COMMUNICATION_TASK__
#define __SERIAL_COMMUNICATION_TASK__

#include "Task.h"
#include "AlarmState.h"
#include "SonarCheckTask.h"
#include "LightCheckTask.h"
#include "LedPowerTask.h"
#include "ServoControlTask.h"
#include "SerialCommunication.h"

#define SEP ";"


class SerialCommunicationTask : public Task {
  AlarmState* alertState = nullptr;
  SonarCheckTask* waterLvl = nullptr;
  ServoControlTask* valve = nullptr;
  LightCheckTask* luminosity = nullptr;
  LedPowerTask* light = nullptr;

  /**
  * returns a string describing the current alarm level
  */
  String alertStateToString(){
    String msg = "NORMAL";
    if (*alertState == PREALARM) {
      msg = "PREALARM";
    }
    if (*alertState == ALARM) {
      msg = "ALARM";
    }
    return msg;
  }

  public:
    SerialCommunicationTask(AlarmState* currState);

    void init(int period, SonarCheckTask* waterLvl, ServoControlTask* valve,
    LightCheckTask* luminosity, LedPowerTask* light);
    void tick();
};

#endif