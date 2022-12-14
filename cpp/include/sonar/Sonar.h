#ifndef __SONAR__
#define __SONAR__

class Sonar {
    int trigPin;
    int echoPin;

    public:
        Sonar(int trigPin, int echoPin);
        int getTrigPin();
        int getEchoPin();
        double calculateDistance(double rawVal);
};

#endif