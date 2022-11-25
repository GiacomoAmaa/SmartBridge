#include "lcd/LCD.h"
#include "lcd/LCDView.h"
#include "utility/BaseView.h"

LCD::LCD() {
    view = new LCDView();
}

void LCD::init() {
    view->init();
    BaseView::printLog("LCD initialization complete");
}

void LCD::print(String message) {
    view->printScreen(message);
    //BaseView::printLog("LCD new msg: " + message)
}