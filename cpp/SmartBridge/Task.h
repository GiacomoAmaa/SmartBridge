#ifndef __TASK__
#define __TASK__

class Task {
    int myPeriod;
    int timeElapsed;
    unsigned long totalTimeElapsed;

    protected:
        int getTotalTimeElapsed() {
            return totalTimeElapsed;
        }

        void setPeriod(int period){
            myPeriod = period;
        }

    public:
        virtual void init(int period){
            setPeriod(period);
            timeElapsed = 0;
            totalTimeElapsed = 0;
        }

        virtual void tick() = 0;

        bool updateAndCheckTime(int basePeriod){
            totalTimeElapsed += basePeriod;
            timeElapsed += basePeriod;
            if (timeElapsed >= myPeriod){
                timeElapsed = 0;
                return true;
            }
            return false;
        }
};

#endif