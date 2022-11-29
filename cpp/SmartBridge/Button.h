#ifndef __BUTTON__
#define __BUTTON__

class Button {
  int pin;

  public:
    /**
    * Button's constructor
    */
    Button(int pin);
    /**
    * Initializes the button
    */
    void init();
    /**
    * Wrapping of the button view method to know if the button is pressed or not
    */
    bool isPressed();
};

#endif