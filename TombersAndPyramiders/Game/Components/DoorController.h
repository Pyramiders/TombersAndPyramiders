#pragma once

#include "BasePossessableController.h"

class DoorController : public BasePossessableController
{
public:
	DoorController(GameObject* parentGameobject, BasePilot* pilot);
	void onPossessionStart();
	void onPossessionEnd();
	void move(Vector2 direction);
	void trigger();
};