#pragma once

#include "ComplexSprite.h"
#include <memory>

//Instance/MovableCharacter
class SpinningEffect : public ComplexSprite
{
private:

public:
	SpinningEffect();
	~SpinningEffect();
    std::shared_ptr<ComplexSpriteInfo> createSpriteInfo();
	void onStart();
	void onUpdate(int ticks);
	void onEnd() {};

};