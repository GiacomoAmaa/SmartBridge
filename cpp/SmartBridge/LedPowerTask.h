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
    int lastBlinkTime = 0;
    int lastDetecTime = 0;
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
        if (lastBlinkTime <= 0) {
            lastBlinkTime = this->getTotalTimeElapsed();
            led->turnOn();
        }
        int blinkTimeElaps = this->getTotalTimeElapsed() - lastBlinkTime;
        BaseView::printLog("blinkTimeElaps: "+String(blinkTimeElaps));
        if (blinkTimeElaps >= BLINK_TIME) {
            if (led->isOff()) {
                led->turnOn();
            } else {
                led->turnOff();
            }
            lastBlinkTime = this->getTotalTimeElapsed();
        }
    }

    void smartLighting(Led* led) {
        int timeElapsFromLastDet = this->getTotalTimeElapsed() - lastDetecTime;
        int currLight = light->getLightLevel();

        led->turnOff();
        if (currLight < MIN_LUMINOSITY && (timeElapsFromLastDet < TIME_INACTIVITY || detector->isMovementDetected())) {
          led->turnOn();
          if (detector->isMovementDetected()){
            lastDetecTime = this->getTotalTimeElapsed();
          }
        }
    }

    public:
        LedPowerTask(AlarmState* currState, int* ledPins, int nleds);
        void init(int period, LightCheckTask* light, PirCheckTask* detector);
        void tick();
};

#endif