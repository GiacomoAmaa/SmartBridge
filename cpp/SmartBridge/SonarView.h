#ifndef __SONAR_VIEW__
#define __SONAR_VIEW__

#define DELAY_HIGH 3
#define DELAY_LOW 5
#define TIMEOUT 20000

#include "BaseView.h"

class SonarView : public BaseView {
    public:
        static void setupPin(int trigPin, int echoPin) {
            BaseView::setupPin(trigPin, OUT);
            BaseView::setupPin(echoPin, IN);
        }

        static float measure(int trigPin, int echoPin) {
            digitalWrite(trigPin,LOW);
            delayMicroseconds(DELAY_HIGH);
            digitalWrite(trigPin,HIGH);
            delayMicroseconds(DELAY_LOW);
            digitalWrite(trigPin,LOW);

            return pulseIn(echoPin, HIGH, TIMEOUT);
        }
};

#endif