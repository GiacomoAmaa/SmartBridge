#include "lcd/LCDView.h"

void LCDView::init() {
    lcd.init();
    lcd.backlight();
}

void LCDView::printScreen(char* message) {
    lcd.print(message);
}