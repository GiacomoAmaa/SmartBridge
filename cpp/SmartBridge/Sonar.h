#ifndef __SONAR__
#define __SONAR__

#define MIN_DISTANCE 0
#define MAX_DISTANCE 343 //cm traveled in 0,02 s

class Sonar {
  int trigPin;
  int echoPin;

  public:
    Sonar(int trigPin, int echoPin);
    int getTrigPin();
    int getEchoPin();
    int calculateDistance(double rawVal);
};

#endif