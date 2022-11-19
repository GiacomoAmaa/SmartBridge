#include "light_sensor/LightCheckTask.h"
#include "light_sensor/LightSensor.h"
#include "light_sensor/LightSensorView.h"

LightCheckTask::LightCheckTask(int pinLs) {
    this->ls=new LightSensor(pinLs);
}

double LightCheckTask::getLightVoltage() {
    return currLight;
}

void LightCheckTask::setPeriod(int period) {
    Task::setPeriod(period/FREQUENCE);
}

void LightCheckTask::init(int period) {
    setPeriod(period);
    LightSensorView::setupPin(ls->getPin(), IN);
}

void LightCheckTask::tick() {
    currLight = ls->calculateVoltage(LightSensorView::measure(ls->getPin()));
}