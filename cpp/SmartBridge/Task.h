#ifndef __TASK__
#define __TASK__

class Task {
  int myPeriod;
  int timeElapsed;

  protected:
    void setPeriod(int period){
      myPeriod = period;
    }

    int getPeriod() {
      return myPeriod;
    }

  public:
    virtual void init(int period){
      setPeriod(period);
      timeElapsed = 0;
    }

    virtual void tick() = 0;

    bool updateAndCheckTime(int basePeriod){
      timeElapsed += basePeriod;
      if (timeElapsed >= myPeriod){
        timeElapsed = 0;
        return true;
      }
      return false;
    }
};

#endif