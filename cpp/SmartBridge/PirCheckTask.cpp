#include "PirCheckTask.h"
#include "PirView.h"
#include "AlarmState.h"

PirCheckTask::PirCheckTask(int pirPin) {
  this->pirPin=pirPin;
}

bool PirCheckTask::isMovementDetected() {
  return detected;
}

void PirCheckTask::init(int period){
  Task::init(period);
  PirView::setupPin(pirPin, IN);
  PirView::calibrate(CALIBRATION_TIME);
  #ifdef DEBUG
    BaseView::printLog("PIR initialization complete");
  #endif
}

void PirCheckTask::tick() {
  detected = PirView::checkMovement(pirPin);
  if (detected) {
    #ifdef DEBUG
      BaseView::printLog("PIR: Movement detected!");
    #endif
  }
}
