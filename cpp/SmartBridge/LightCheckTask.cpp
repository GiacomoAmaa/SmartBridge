#include "LightCheckTask.h"
#include "LightSensor.h"
#include "LightSensorView.h"

LightCheckTask::LightCheckTask(int pinLs) {
    this->ls=new LightSensor(pinLs);
}

int LightCheckTask::getLightLevel() {
    return currLight;
}

void LightCheckTask::setPeriod(int period) {
    Task::setPeriod(period/FREQUENCE);
}

void LightCheckTask::init(int period) {
    setPeriod(period);
    LightSensorView::setupPin(ls->getPin(), IN);
    #ifdef DEBUG
    BaseView::printLog("Fotoresistor initialization complete");
    #endif
}

void LightCheckTask::tick() {
    currLight = ls->calculateLightLevel(LightSensorView::measure(ls->getPin()));
    #ifdef DEBUG
    BaseView::printLog("Light intensity: " + String(currLight));
    #endif
}