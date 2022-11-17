#include "sonar/Sonar.h"

Sonar::Sonar(int trigPin, int echoPin) {
    this->trigPin=trigPin;
    this->echoPin=echoPin;
}

int Sonar::getTrigPin() {
    return trigPin;
}

int Sonar::getEchoPin() {
    return echoPin;
}

float Sonar::calculateDistance(float echoSig) {
    const float vs = 331.45 + 0.62*20;
    float t = echoSig / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}