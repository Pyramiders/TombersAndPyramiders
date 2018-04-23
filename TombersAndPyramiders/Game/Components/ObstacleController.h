#pragma once

#include "BasePossessableController.h"
#include "ObstaclePilot.h"

class ObstacleController : public BasePossessableController
{
public:
	ObstacleController(GameObject* parentGameobject, ObstaclePilot* pilot);
	void onPossessionStart();
	void onPossessionEnd();
	void move(Vector2 direction);
	void trigger();
};