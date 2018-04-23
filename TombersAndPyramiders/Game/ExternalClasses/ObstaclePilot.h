#pragma once

#include "BasePilot.h"
#include "TimeInterval.h"
#include <memory>

class ObstaclePilot : public BasePilot
{
private:
	int timePassed = 0;
	int nextUpdate = 1000;
public:
	ObstaclePilot() {
		
	};
	void onStart();
	void onUpdate(int ticks);
	void onEnd() {}
};
