#include "ObstacleController.h"
#include "Obstacles/Obstacle.h"

ObstacleController::ObstacleController(GameObject* parentGameobject, ObstaclePilot* pilot) : BasePossessableController(parentGameobject, pilot)
{

}

void ObstacleController::trigger()
{
	Obstacle* obstacle = dynamic_cast<Obstacle*>(gameObject);
	if (obstacle != nullptr)
	{
		switch (obstacle->getState())
		{
		case Obstacle::Mode::Enabled:
			obstacle->setState(Obstacle::Mode::Disabled);
			break;
		case Obstacle::Mode::Disabled:
			obstacle->setState(Obstacle::Mode::Enabled);
			break;
		default:
			break;
		}
	}
}

void ObstacleController::onPossessionStart()
{
	//Void
}

void ObstacleController::onPossessionEnd()
{
	//Void
}

void ObstacleController::move(Vector2 direction)
{
	//Void
}