#ifndef __LED__
#define __LED__

#define MIN_LED_INTENSITY 0
#define MAX_LED_INTENSITY 255

class Led {
    int pin;
    int lightIntensity = 0;
    
    public:
        Led(int pin);
        bool isOn();
        bool isOff();
        int getCurrIntensity();
        int getPin();
        void turnOn();
        void turnOff();
        void increaseIntensity(int intensity);
        void decreaseIntensity(int intensity);
};

#endif