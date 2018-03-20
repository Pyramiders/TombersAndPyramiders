#pragma once

#include "GameObject.h"
#include "Vector2.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

class Rigidbody : public Component
{
private:
	BoxCollider* m_boxCollider;

	Vector2 m_velocity;
	float m_frictionCoefficient;

public:
	Rigidbody(GameObject* gameObject, BoxCollider* collider);
	void BlockMovement();
	void setVelocity(Vector2 v);
	void setFrictionCoefficient(float friction);
	void addVelocity(Vector2 v);
	Vector2 getVelocity();

	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};

};