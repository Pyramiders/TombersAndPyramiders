#pragma once

#include "ComplexSprite.h"
#include "Invokable.h"

class Throne : public ComplexSprite, public Invokable
{
private:
    bool m_popupActive;
    std::shared_ptr<ComplexSpriteInfo> createSpriteInfo();
    float m_brightness;
    bool m_activated;
    float m_counter;

public:
	Throne();
	~Throne();

	void onStart();
	void onUpdate(int ticks);
    void onEnd() {};
    void trigger();
};