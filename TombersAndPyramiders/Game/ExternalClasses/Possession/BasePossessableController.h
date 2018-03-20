#pragma once
#include "BaseController.h"
#include "Invokable.h"

extern class GameObject;
extern class BasePilot;

//Controller Component for objects which can be controlled via Possession
class BasePossessableController : public BaseController, public Invokable {
public:
	BasePossessableController(GameObject* parentGameobject, BasePilot* pilot);
	virtual void onPossessionStart() = 0;
	virtual void onPossessionEnd() = 0;
	virtual void move(Vector2 direction) = 0;
};