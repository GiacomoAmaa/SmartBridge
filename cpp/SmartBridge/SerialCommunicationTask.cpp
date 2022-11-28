#include "SerialCommunicationTask.h"

SerialCommunicationTask::SerialCommunicationTask(AlarmState* currState) {
    this->alertState = currState;
}

void SerialCommunicationTask::init(int period, SonarCheckTask* waterLvl,
  ServoControlTask* valve, LightCheckTask* luminosity, LedPowerTask* light) {
    Task::init(period);
    this->waterLvl = waterLvl;
    this->valve = valve;
    this->luminosity = luminosity;
    this->light = light;
    MsgService.init();
}

void SerialCommunicationTask::tick() {
  MsgService.sendMsg(alertStateToString() + SEP +
    light->getSmartLightStatus() + SEP + valve->getValveControl()
    + SEP + String(waterLvl->getCurrentHeightLvl()) 
    + SEP + String(luminosity->getLightLevel())
    + SEP + String(valve->getCurrValveOpening()));
  if(MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();
    msg->getContent();
  }
}
