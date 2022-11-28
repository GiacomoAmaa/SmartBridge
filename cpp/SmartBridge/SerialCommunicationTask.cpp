#include "SerialCommunicationTask.h"

SerialCommunicationTask::SerialCommunicationTask(AlarmState* currState, SonarCheckTask* waterLvl,
  ServoControlTask* valve, LightCheckTask* luminosity, LedPowerTask* light) {
    this->alertState = currState;
    this->waterLvl = waterLvl;
    this->valve = valve;
    this->luminosity = luminosity;
    this->light = light;
}

void SerialCommunicationTask::init() {
  MsgService.init();
}

void SerialCommunicationTask::tick() {
  MsgService.sendMsg("a");
  if(MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();
    msg->getContent();
  }
}
