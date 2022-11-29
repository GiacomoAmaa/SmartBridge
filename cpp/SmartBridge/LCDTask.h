#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "LCDView.h"
#include "Task.h"

#define MAX_ROWS 2
#define MAX_COLS 16

class LCDTask : public Task {
    LCDView* view = nullptr;
    String lines[MAX_ROWS];
    int currRow = 0;

    public:
        LCDTask();
        void init(int period);
        void appendMsg(String msg);
        void tick();
};

#endif