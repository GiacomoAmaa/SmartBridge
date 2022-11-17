#ifndef __LED_TASK__
#define __LED_TASK__

#include "Led.h"
#include "../scheduler/Task.h"
#include "../utility/AlarmState.h"

class LedPowerTask : public Task {
    AlarmState* currState = nullptr;
    Led* leds = nullptr;
    int nleds = 0;

    void updateLeds() {
        for (int i=0; i<nleds; i++){
            LedView::setLedIntensity(leds[i].getPin(), leds[i].getCurrIntensity());
        }
    }

    public:
        LedPowerTask(AlarmState* currState, Led* leds, int nleds);
        void init(int period);
        void tick();
};

#endif