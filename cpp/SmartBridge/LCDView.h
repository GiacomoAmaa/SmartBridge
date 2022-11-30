#ifndef __LCD_VIEW__
#define __LCD_VIEW__

#include <LiquidCrystal_I2C.h>
#include "BaseView.h"

#define ADDRESS 0x27
#define MAX_ROWS 2
#define MAX_COLS 16

class LCDView : public BaseView {
  
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(ADDRESS, MAX_COLS, MAX_ROWS);

  public:
    void init();
    /**
    * prints the given string at the given coordinates on lcd screen
    */
    void printLayout(int row, String msg);
    /**
    * cleans up the lcd screen
    */
    void clean();
};

#endif