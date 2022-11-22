#include "lcd/LCD.h"
#include "lcd/LCDView.h"

LCD::LCD() {
    view = new LCDView();
    view->init();
}

void LCD::print(char* message) {
    view->printScreen(message);
}