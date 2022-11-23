#include "lcd/LCD.h"
#include "lcd/LCDView.h"

LCD::LCD() {
    view = new LCDView();
}

void LCD::init() {
    view->init();
}

void LCD::print(char* message) {
    view->printScreen(message);
}