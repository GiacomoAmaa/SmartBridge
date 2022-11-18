#ifndef __LED_TASK__
#define __LED_TASK__

#include "Led.h"
#include "../scheduler/Task.h"
#include "../utility/AlarmState.h"

#define BLINK_TIME 2000

class LedPowerTask : public Task {
    AlarmState* currState = nullptr;
    Led* leds = nullptr;
    int nleds = 0;
    int blinkInitTime = 0;

    void updateLeds() {
        for (int i=0; i<nleds; i++){
            LedView::setLedState(leds[i].getPin(), leds[i].isOn() ? ON : OFF);
        }
    }

    void blinkLed(Led* led, int blinkTime) {
        blinkInitTime = blinkInitTime <= 0 ? this->getTotalTimeElapsed() : blinkInitTime;
        int blinkTimeElaps = this->getTotalTimeElapsed() - blinkInitTime;
        if (blinkTimeElaps <= blinkTime) {
            if (led->isOff()) {
                led->turnOn();
            } else if (led->isOn()) {
                led->turnOff();
            }
        } else {
            led->turnOff();
        }
    }

    public:
        LedPowerTask(AlarmState* currState, Led* leds, int nleds);
        void init(int period);
        void tick();
};

#endif