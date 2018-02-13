#pragma once

#include "Collider.h"
#include "Vector2.h"

class BoxCollider : public Collider {
private:
	float m_width, m_height;
public:
	BoxCollider(GameObject* parentGameObject, float width, float height);
	float getWidth();
	float getHeight();
	void setWidth(float width);
	void setHeight(float height);
};