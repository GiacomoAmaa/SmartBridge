#include "led/Led.h"
#include "led/LedView.h"
#include "led/LedPowerTask.h"

LedPowerTask::LedPowerTask(AlarmState* currState, Led* leds, int nleds){
    this->currState=currState;
    this->leds=leds;
    this->nleds=nleds;
}

void LedPowerTask::init(int period){
    Task::init(period);
    for (int i=0; i<nleds; i++) {
        LedView::setupPin(leds[i].getPin(), OUT);
    }
    updateLeds();
}

void LedPowerTask::tick(){
    updateLeds();
    switch(*currState) {
        case ALARM:
            blinkInitTime = 0;
            leds[0].turnOff();
            leds[1].turnOff();
            leds[2].turnOn();
            break;
        case PREALARM:
            // leds[0] - Smart light working
            leds[1].turnOn();
            blinkLed(&leds[2], BLINK_TIME);
            break;
        default:
            blinkInitTime = 0;
            // leds[0] - Smart light working
            leds[1].turnOn();
            leds[2].turnOff();
            break;
    }
}