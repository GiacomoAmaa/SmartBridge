#include "LCDView.h"

void LCDView::init() {
  lcd.init();
}

void LCDView::printScreen(int col, String msg) {
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, col);
  lcd.print(msg);
}

void LCDView::clean(){
  lcd.clear();
  lcd.noBacklight();
}
