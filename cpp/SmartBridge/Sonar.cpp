#include "Sonar.h"

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

int Sonar::calculateDistance(double rawVal) {
    if(rawVal != 0){
      const double vs = 331.45 + 0.62*20;
      double t = rawVal / 1000.0 / 1000.0 / 2;
      return t*vs*100;  //distance in cm
    }
    return MAX_DISTANCE;
}