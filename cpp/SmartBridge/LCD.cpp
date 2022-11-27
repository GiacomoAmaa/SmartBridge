#include "LCD.h"
#include "LCDView.h"
#include "BaseView.h"

LCD::LCD() {
    view = new LCDView();
}

void LCD::init() {
    view->init();
    BaseView::printLog("LCD initialization complete");
}

void LCD::print(String frstline, String scndline) {
    view->printScreen(frstline, scndline);
    //BaseView::printLog("LCD new msg: " + message)
}

void LCD::clean() {
    view->clean();
}