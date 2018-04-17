#pragma once

#include "BaseController.h"

extern class Vector2;
extern class BasePilot;
extern class GhostCharacter;
extern class BasePossessableController;

class GhostController : public BaseController
{
private:
	static const float MAX_POSSESSION_DISTANCE;
	static Vector2 DEFAULT_MOVE_SPEED;
	std::shared_ptr<BasePossessableController> m_toFollow;

public:
	GhostController(GameObject* parentGameobject, BasePilot* pilot = nullptr);

	void onUpdate(int ticks);
	void onStart();
	void move(Vector2 moveInput);
	void follow(std::shared_ptr<BasePossessableController> toFollow);
	bool tryPossess(std::shared_ptr<BasePossessableController> toPossess);
	bool tryPossessClosest(std::shared_ptr<BasePossessableController>& toPopulate);
	bool tryTrigger();
	void stopPossessing();
	std::shared_ptr<BasePossessableController> getPossessingItem();
};
