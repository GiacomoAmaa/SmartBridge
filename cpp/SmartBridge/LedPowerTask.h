#ifndef __LED_TASK__
#define __LED_TASK__

#include "Led.h"
#include "LedView.h"
#include "Task.h"
#include "AlarmState.h"
#include "PirCheckTask.h"
#include "LightCheckTask.h"

#define BLINK_TIME 2000
#define MIN_LUMINOSITY 30
#define TIME_INACTIVITY 5000

class LedPowerTask : public Task {
    AlarmState* currState = nullptr;
    PirCheckTask* detector = nullptr;
    LightCheckTask* light = nullptr;
    Led* leds = nullptr;
    int blinkTimeElaps = 0;
    int detecTimeElaps = 0;
    int nleds = 0;

    void updateLeds() {
        for (int i=0; i<nleds; i++){
            LedView::setLedState(leds[i].getPin(), leds[i].isOn() ? ON : OFF);
        }
    }

    void printLedState() {
      for (int i=0; i<nleds; i++){
        BaseView::printLog("Led " + String(i+1) + " - " + (leds[i].isOn() ? "ON" : "OFF"));
      }
    }

    void blinkLed(Led* led) {
        blinkTimeElaps += this->getPeriod();
        BaseView::printLog("blinkTimeElaps: "+String(blinkTimeElaps));
        if (blinkTimeElaps >= BLINK_TIME) {
            if (led->isOff()) {
                led->turnOn();
            } else {
                led->turnOff();
            }
            blinkTimeElaps = 0;
        }
    }

    void smartLighting(Led* led) {
        int currLight = light->getLightLevel();

        led->turnOff();
        if (currLight < MIN_LUMINOSITY && (detecTimeElaps < TIME_INACTIVITY || detector->isMovementDetected())) {
          detecTimeElaps += this->getPeriod();
          led->turnOn();
          if (detector->isMovementDetected()){
            detecTimeElaps = 0;
          }
        }
    }

    public:
        LedPowerTask(AlarmState* currState, int* ledPins, int nleds);
        void init(int period, LightCheckTask* light, PirCheckTask* detector);
        void tick();
};

#endif