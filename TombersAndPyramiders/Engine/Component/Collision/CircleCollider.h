#pragma once

#include "Collider.h"

class CircleCollider : public Collider {
private:
	float m_radius;
public:
	CircleCollider(float radius);
	float getRadius();
	void setRadius(float radius);
};