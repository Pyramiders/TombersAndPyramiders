#pragma once
#include "BasePossessableController.h"

extern class Rigidbody;
extern class DamagingRegion;

//Possessable Boulder that ghosts can control. WASD to move, Space to launch the boulder in the direction its traveling (it only does damage during launch)
class BoulderController : public BasePossessableController {
private:
	static const float MAX_MOVESPEED;
	static const float FRICTION;
	static const float COOLDOWN;
	std::shared_ptr<Rigidbody> m_rigidBody;
	std::shared_ptr<DamagingRegion> m_damagingRegion;
	float m_cooldownTicker;

public:
	BoulderController(GameObject* parentGameobject, BasePilot* pilot);
	virtual void onPossessionStart();
	virtual void onPossessionEnd();
	virtual void move(Vector2 direction);
	virtual void trigger();
};