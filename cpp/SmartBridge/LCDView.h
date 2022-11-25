#ifndef __LCD_VIEW__
#define __LCD_VIEW__

#include <LiquidCrystal_I2C.h> 
#include "BaseView.h"

#define ADDRESS 0x27
#define ROWS 20
#define COLS 4

class LCDView : public BaseView {
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(ADDRESS, ROWS, COLS);
    public:
        void init();
        void printScreen(String message);
};

#endif