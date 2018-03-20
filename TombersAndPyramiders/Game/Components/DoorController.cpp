#include "DoorController.h"
#include "Door.h"

DoorController::DoorController(GameObject* parentGameobject, BasePilot* pilot) : BasePossessableController(parentGameobject, pilot)
{

}

void DoorController::trigger()
{
	//Open-Close Door

	Door* door = dynamic_cast<Door*>(gameObject);
	if (door != nullptr)
	{
		switch (door->getState())
		{
		case Door::Mode::Open:
			door->setState(Door::Mode::Closed);
			break;
		case Door::Mode::Closed:
			door->setState(Door::Mode::Open);
			break;
		default:
			break;
		}
	}
}

void DoorController::onPossessionStart()
{
	//Void
}

void DoorController::onPossessionEnd()
{
	//Void
}

void DoorController::move(Vector2 direction)
{
	//Void
}