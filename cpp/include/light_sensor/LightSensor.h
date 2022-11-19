#ifndef __LIGHT_SENSOR__
#define __LIGHT_SENSOR__

class LightSensor {
    int pin;

    public:
        LightSensor(int pin);
        int getPin();
        double calculateVoltage(int rawVal);
};

#endif