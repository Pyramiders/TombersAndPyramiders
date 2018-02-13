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

public:
	Rigidbody(GameObject* gameObject, BoxCollider* collider);
	void BlockMovement();
	void setVelocity(Vector2 v);

	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};

};