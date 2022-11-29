#ifndef __BUTTON__
#define __BUTTON__

class Button {
  int pin;

  public:
    Button(int pin);
    void init();
    bool isPressed();
};

#endif