#include "Door.h"
#include "DoorController.h"
#include "DummyPilot.h"
#include "SpawnManager.h"
#include "PositionBasedPopup.h"
#include "GameManager.h"

Door::Door(std::shared_ptr<ComplexSpriteInfo> spriteInfo, Vector2* colliderOffset, Direction direction, Mode mode, float x, float y, float scale) : ComplexSprite(spriteInfo, x, y)
{
	getTransform()->setScale(scale);
	m_mode = mode;
	changeSpriteSheet(mode);
	addComponentAsParent<DoorController, BasePossessableController>(this, new DummyPilot());
	addComponent<BoxCollider>(this, colliderOffset->getX(), colliderOffset->getY()); //Offset of colliderOffset->getX(), colliderOffset->getY() when offset added
	delete colliderOffset;
	m_popupActive = false;
}

void Door::onUpdate(int ticks)
{
	updateFrames(ticks);
	auto character = SpawnManager::getInstance()->getActivePlayer();
	if (character != nullptr)
	{
		auto distance = getTransform()->getDistance(character->getTransform());
		if (distance < 4.0f && !m_popupActive)
		{
			m_popupActive = true;
			GameManager::getInstance()->createGameObject<PositionBasedPopup>(false, getTransform()->getX(), getTransform()->getY(), 4.0f, character, "popupActive.png");
			//Create Popup to destroy when this & player are 4> distance apart
		}
		else if (distance > 4.0f) {
			m_popupActive = false;
		}
	}
}

void Door::setState(Mode mode)
{
	m_mode = mode;
	switch (m_mode)
	{
	case Door::Open:
		changeSpriteSheet(Open);
		getComponent<BoxCollider>()->setDisabled(true);
		break;
	case Door::Closed:
		changeSpriteSheet(Closed);
		getComponent<BoxCollider>()->setDisabled(false);
		break;
	default:
		break;
	}
}

Door::Mode Door::getState()
{
	return m_mode;
}