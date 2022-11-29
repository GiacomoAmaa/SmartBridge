#include "LCDView.h"

void LCDView::init() {
  lcd.init();
  lcd.backlight();
}

void LCDView::printLayout(int row, String msg) {
  lcd.setCursor(0, row);
  lcd.print(msg);
}

void LCDView::clean(){
  lcd.clear();
}

