#ifndef __LED__
#define __LED__

typedef enum {ON, OFF} LedState;

class Led {
    int pin;
    LedState state;
    
    public:
        Led(int pin);
        bool isOn();
        bool isOff();
        int getPin();
        void turnOn();
        void turnOff();
};

#endif