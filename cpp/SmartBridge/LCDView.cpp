#include "LCDView.h"

void LCDView::init() {
  lcd.init();
  lcd.backlight();
}

void LCDView::printLayout(int col, int row, String msg) {
  lcd.setCursor(col, row);
  lcd.print(msg);
}

void LCDView::clean(){
  lcd.clear();
}

