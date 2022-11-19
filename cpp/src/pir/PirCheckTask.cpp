#include "pir/PirCheckTask.h"
#include "pir/PirView.h"
#include "utility/AlarmState.h"

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
}

void PirCheckTask::tick() {
    detected = PirView::checkMovement(pirPin);
}