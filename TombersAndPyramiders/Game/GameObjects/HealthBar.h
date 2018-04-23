#pragma once

#include "ComplexSprite.h"

//On game start, visible, counting down
//Whenever hit message received, reappear then count down
//On count down reaching zero, shrink

class HealthBar : public ComplexSprite
{
private:
	std::shared_ptr<GameObject> m_playerToTrack;
	bool m_visible;
	int m_timeTilDissapear;
	float m_mainSize;
	int m_subscriptionID;

	std::shared_ptr<ComplexSpriteInfo> createSpriteInfo();

public:
	HealthBar();
	~HealthBar();

	void onStart();
	void onUpdate(int ticks);
	void onEnd() {};
	void setTrackingPlayer(std::shared_ptr<GameObject> playerToTrack);
	void updateHealth(float currentHealth, float maxHealth);
};