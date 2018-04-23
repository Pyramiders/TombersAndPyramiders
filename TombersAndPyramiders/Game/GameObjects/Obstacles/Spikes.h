#pragma once

#include "ComplexSprite.h"
#include "Vector2.h"
#include "Obstacle.h"
#include "DamagingRegion.h"

class Spikes : public Obstacle
{
	public:
	Spikes(Direction direction, Mode mode, float startX, float startY, float scale);
	std::shared_ptr<ComplexSpriteInfo> createSpriteInfo();
	void setState(Mode mode);

	private:
	std::shared_ptr<DamagingRegion> m_damagingRegion;
};