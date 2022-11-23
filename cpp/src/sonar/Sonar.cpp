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

double Sonar::calculateDistance(double rawVal) {
    const double vs = 331.45 + 0.62*20;
    double t = rawVal / 1000.0 / 1000.0 / 2;
    double d = t*vs;
    return d;
}