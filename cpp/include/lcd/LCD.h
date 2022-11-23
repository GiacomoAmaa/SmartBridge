#ifndef __LCD__
#define __LCD__

#include "LCDView.h"

class LCD {
    LCDView* view = nullptr;

    public:
        LCD();
        void init();
        void print(char* message);
};

#endif