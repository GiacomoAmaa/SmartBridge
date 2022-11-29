#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#define POT_MIN_VALUE 0
#define POT_MAX_VALUE 1024

class Potentiometer {
  int pin;

  public:
    Potentiometer(int pin);
    void init();
    int getRotation();
};

#endif