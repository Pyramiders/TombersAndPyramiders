#pragma once

#include "SimpleSprite.h"

class PositionBasedPopup : public SimpleSprite
{
private:
	float m_maxDistance;
	std::shared_ptr<GameObject> m_dependant;

public:
	PositionBasedPopup(float x, float y, float maxDistance, std::shared_ptr<GameObject> dependant, std::string imageName);
	~PositionBasedPopup();

	void onStart();
	void onUpdate(int ticks);
	void onEnd() {};
};
