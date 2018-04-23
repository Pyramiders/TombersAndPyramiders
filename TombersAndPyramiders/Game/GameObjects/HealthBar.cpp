#include "HealthBar.h"
#include "MessageManager.h"
#include <sstream>

/*
Message manager callback:

*/

void updateHealthBarCallback(std::map<std::string, void*> data) {
	HealthBar* healthBar = (HealthBar*)data["this"];
	int currentHealth = std::stoi(*(std::string*)data["currentHealth"]);
	int maxHealth = std::stoi(*(std::string*)data["maxHealth"]);
	healthBar->updateHealth(currentHealth, maxHealth);
}


HealthBar::HealthBar() : ComplexSprite(createSpriteInfo(), 0, 0, 1.0f, 2.0f)
{
	m_visible = true;
	m_timeTilDissapear = 3000;
	m_subscriptionID = 0;
}

std::shared_ptr<ComplexSpriteInfo> HealthBar::createSpriteInfo()
{
	auto spriteInfo = std::make_shared<ComplexSpriteInfo>();
	spriteInfo->addSprite("healthBarSheet.png", "HealthBar", 10, 1);
	spriteInfo->addAnimation("HealthBar", "8", 0, 0);
	spriteInfo->addAnimation("HealthBar", "7", 1, 1);
	spriteInfo->addAnimation("HealthBar", "6", 2, 2);
	spriteInfo->addAnimation("HealthBar", "5", 3, 3);
	spriteInfo->addAnimation("HealthBar", "4", 4, 4);
	spriteInfo->addAnimation("HealthBar", "3", 5, 5);
	spriteInfo->addAnimation("HealthBar", "2", 6, 6);
	spriteInfo->addAnimation("HealthBar", "1", 7, 7);
	spriteInfo->addAnimation("HealthBar", "0", 8, 8);

	return spriteInfo;
}

void HealthBar::onStart()
{
	changeAnimation("8");
}

void HealthBar::onUpdate(int ticks)
{
	if (m_timeTilDissapear >= 0) {
		m_timeTilDissapear -= ticks > 60 ? 60 : ticks;
	}
	else {
		if (getTransform()->getScale() > 0) {
			m_mainSize = getTransform()->getScale();
			getTransform()->setScale(0.0f);
		}
	}
	if (m_playerToTrack != nullptr) {
		getTransform()->setPosition(m_playerToTrack->getTransform()->getX(), m_playerToTrack->getTransform()->getY());
	}
}

HealthBar::~HealthBar()
{
	
}

void HealthBar::setTrackingPlayer(std::shared_ptr<GameObject> playerToTrack)
{
	if (m_subscriptionID != 0) {
		std::stringstream oldEvent;
		oldEvent << m_playerToTrack->getId() << "|HEALTHBAR";
		MessageManager::unSubscribe(oldEvent.str(), m_subscriptionID);
	}
	m_playerToTrack = playerToTrack;
	std::stringstream newEvent;
	newEvent << m_playerToTrack->getId() << "|HEALTHBAR";
	m_subscriptionID = MessageManager::subscribe(newEvent.str(), updateHealthBarCallback, this);
}

void HealthBar::updateHealth(float currentHealth, float maxHealth) {
	float percent = currentHealth / maxHealth * 100;
	std::string animationName;

	//setCurrentSpriteIndex(0) is full, setCurrentSpriteIndex(9) is 0% health. hmm
	if (percent >= 92) {
		animationName = "Full";
	} else if (percent >= 88) {
		animationName = "8";
	} else if (percent >= 77) {
		animationName = "7";
	} else if (percent >= 66) {
		animationName = "6";
	} else if (percent >= 55) {
		animationName = "5";
	} else if (percent >= 44) {
		animationName = "4";
	} else if (percent >= 33) {
		animationName = "3";
	} else if (percent >= 22) {
		animationName = "2";
	}  else if (percent >= 11) {
		animationName = "1";
	}  else {
		animationName = "0";
	}
	changeAnimation(animationName);
	//setCurrentSpriteIndex(spriteIndex);
	getTransform()->setScale(m_mainSize);
	m_timeTilDissapear = 600;
}