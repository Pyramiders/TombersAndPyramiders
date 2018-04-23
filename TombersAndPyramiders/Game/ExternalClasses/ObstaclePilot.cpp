#include "ObstaclePilot.h"
#include <cmath>
#include "Randomize.h"
#include "ObstacleController.h"

void ObstaclePilot::onStart()
{

}

void ObstaclePilot::onUpdate(int ticks)
{
	timePassed += ticks;
	if (timePassed >= nextUpdate) {
		auto ob = dynamic_cast<ObstacleController *>(m_controller);
		if (ob != nullptr)
		{
			ob->trigger();
		}
		timePassed -= nextUpdate;
	}
}

