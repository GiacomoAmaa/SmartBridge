#include "LedPowerTask.h"
#include "Led.h"
#include "LedView.h"
#include "PirCheckTask.h"
#include "LightCheckTask.h"

LedPowerTask::LedPowerTask(AlarmState* currState, int* ledPins, int nleds){
    this->currState=currState;
    this->nleds=nleds;
    
    this->leds = (Led*)malloc(sizeof(Led)*nleds);
    for (int i=0; i<nleds; i++){
        leds[i] = Led(ledPins[i]);
    }
}

void LedPowerTask::init(int period, LightCheckTask* light, PirCheckTask* detector){
    Task::init(period);
    this->light=light;
    this->detector=detector;
    for (int i=0; i<nleds; i++) {
        LedView::setupPin(leds[i].getPin(), OUT);
        leds[i].turnOff();
    }
    updateLeds();
    #ifdef DEBUG
    BaseView::printLog("Led scheduler initialization complete");
    #endif
}

void LedPowerTask::tick(){
    switch(*currState) {
        case ALARM:
            detecTimeElaps = TIME_INACTIVITY;
            leds[0].turnOff();
            leds[1].turnOff();
            leds[2].turnOn();
            break;
        case PREALARM:
            smartLighting(&leds[0]);
            leds[1].turnOn();
            blinkLed(&leds[2]);
            break;
        default:
            smartLighting(&leds[0]);
            leds[1].turnOn();
            leds[2].turnOff();
            break;
    }
    updateLeds();
    printLedState();
}

String LedPowerTask::getSmartLightStatus() {
  return leds[0].isOn() ? "ON" : "OFF";
}
