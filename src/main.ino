#include "Scheduler.h"

Scheduler taskmgr;


void setup(){
    taskmgr.init(50);
}

void loop(){
    taskmgr.schedule();
}