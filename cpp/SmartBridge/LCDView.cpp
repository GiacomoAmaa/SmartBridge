#include "LCDView.h"

void LCDView::init(int cols, int rows) {
    lcd.init();
    lcd.begin(cols, rows);
    lcd.backlight();
}

void LCDView::printScreen(int col, String msg) {
    lcd.setCursor(0, col);
    lcd.print(msg);
}

void LCDView::clean(){
    lcd.clear();
}