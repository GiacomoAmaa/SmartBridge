#include "pir/PirCheckTask.h"
#include "pir/PirView.h"
#include "utility/AlarmState.h"

PirCheckTask::PirCheckTask(AlarmState* currState, int pirPin) {
    this->currState=currState;
    this->pirPin=pirPin;
}

bool PirCheckTask::movementDetected() {
    return detected;
}

void PirCheckTask::init(int period){
    Task::init(period);
    PirView::setupPin(pirPin, IN);
}

void PirCheckTask::tick() {
    detected = PirView::checkMovement(pirPin);
}