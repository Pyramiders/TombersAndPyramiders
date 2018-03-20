#pragma once

#include "Collider.h"

class CircleCollider : public Collider {
private:
	float m_radius;
public:
	CircleCollider(GameObject* gameObject, float radius);
	CircleCollider(GameObject* gameObject, float radius, float xPos, float yPos);
	float getRadius();
	void setRadius(float radius);
};