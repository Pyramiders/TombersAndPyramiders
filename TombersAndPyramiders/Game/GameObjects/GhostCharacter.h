#pragma once

#include "ComplexSprite.h"
#include "Audio\AudioListener.h"

extern class BasePilot;


class GhostCharacter : public ComplexSprite
{
public:
	enum Mode { ghost, possessing };

	GhostCharacter(BasePilot* pilot);
	~GhostCharacter();

	void onStart();
	void onUpdate(int ticks);
	void onEnd() {};
	void setMode(Mode mode);
	Mode getMode();

private:
	static const float MIN_POSSESS_SIZE;
	static const float MAX_POSSESS_SIZE;
	static const float SIZE_CHANGE_RATE;

	Mode m_mode;

	float m_sizeChange;

	std::shared_ptr<ComplexSpriteinfo> createSpriteInfo();
};