#ifndef __LED_TASK__
#define __LED_TASK__

#include "Led.h"
#include "LedView.h"
#include "Task.h"
#include "AlarmState.h"
#include "PirCheckTask.h"
#include "LightCheckTask.h"

#define BLINK_TIME 2000
#define LIGHT_SENSITIVITY 100
#define TIME_INACTIVITY 5000

class LedPowerTask : public Task {
    AlarmState* currState = nullptr;
    PirCheckTask* detector = nullptr;
    LightCheckTask* light = nullptr;
    Led* leds = nullptr;
    int blinkInitTime = 0;
    int lastDetecTime = 0;
    int nleds = 0;

    void updateLeds() {
        for (int i=0; i<nleds; i++){
            LedView::setLedState(leds[i].getPin(), leds[i].isOn() ? ON : OFF);
            BaseView::printLog("Led " + String(i+1) + " - " + (leds[i].isOn() ? "ON" : "OFF"));
        }
    }

    void blinkLed(Led* led) {
        blinkInitTime = blinkInitTime <= 0 ? this->getTotalTimeElapsed() : blinkInitTime;
        int blinkTimeElaps = this->getTotalTimeElapsed() - blinkInitTime;
        if (blinkTimeElaps <= BLINK_TIME) {
            if (led->isOff()) {
                led->turnOn();
            } else if (led->isOn()) {
                led->turnOff();
            }
        } else {
            led->turnOff();
        }
    }

    void smartLighting(Led* led) {
        double currLight = light->getLightVoltage();
        if (currLight < LIGHT_SENSITIVITY || detector->isMovementDetected()) {
            lastDetecTime = this->getTotalTimeElapsed();
            led->turnOn();
            return;
        }
        int timeElapsFromLastDet = this->getTotalTimeElapsed() - lastDetecTime;
        if (timeElapsFromLastDet >= TIME_INACTIVITY) {
            led->turnOff();
        }
    }

    public:
        LedPowerTask(AlarmState* currState, int* ledPins, int nleds);
        void init(int period, LightCheckTask* light, PirCheckTask* detector);
        void tick();
};

#endif