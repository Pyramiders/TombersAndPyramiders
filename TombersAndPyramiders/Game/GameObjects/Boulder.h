#pragma once

#include "ComplexSprite.h"

class Boulder : public ComplexSprite
{
private:
	float m_lastX;
	float m_lastY;
	float m_distTraveled;
	std::shared_ptr<ComplexSpriteinfo> createSpriteInfo();

public:
	Boulder(BasePilot* pilot);
	~Boulder();

	void onStart();
	void onUpdate(int ticks);
	void onEnd() {};

};