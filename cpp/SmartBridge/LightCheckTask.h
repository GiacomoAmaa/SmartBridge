#ifndef __LIGHT_TASK__
#define __LIGHT_TASK__

#include "LightSensor.h"
#include "LightSensorView.h"
#include "Task.h"

#define FREQUENCE 5

class LightCheckTask : public Task {
	LightSensor* ls;
	double currLight = 0.0;

	public:
		LightCheckTask(int pinLs);
		int getLightLevel();
		void setPeriod(int period);
		void init(int period);
		void tick();
};

#endif