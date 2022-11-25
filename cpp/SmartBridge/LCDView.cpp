#include "LCDView.h"

void LCDView::init() {
    lcd.init();
    lcd.backlight();
}

void LCDView::printScreen(String message) {
    lcd.setCursor(0, 0);
    lcd.print(message);
}