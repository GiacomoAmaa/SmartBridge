#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "LCDView.h"
#include "Task.h"

#define MAX_COLS 10

class LCDTask : public Task {
    LCDView* view = nullptr;
    String lines[MAX_COLS];
    int currCol = 0;

    public:
        LCDTask();
        void init(int period);
        void appendMsg(String msg);
        void tick();
};

#endif