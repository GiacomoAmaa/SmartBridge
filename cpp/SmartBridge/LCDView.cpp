#include "LCDView.h"

void LCDView::init() {
    lcd.init();
    lcd.backlight();
}

void LCDView::printScreen(String frstline, String scndline) {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(frstline);
    lcd.setCursor(0, 1);
    lcd.print(scndline);
}

void LCDView::clean(){
    lcd.clear();
    lcd.noBacklight();
}