#ifndef __LED__
#define __LED__

typedef enum {ON, OFF} LedState;

class Led {
  int pin;
  LedState state;
    
  public:
    Led(int pin);
    /**
    * returns true id the led is on
    */
    bool isOn();
    /**
    * returns true id the led is off
    */
    bool isOff();
    /**
    * returns the pin in which is plugged the led
    */
    int getPin();
    /**
    * Turns on the pin
    */
    void turnOn();
    /**
    * Turns off the pin
    */
    void turnOff();
};

#endif