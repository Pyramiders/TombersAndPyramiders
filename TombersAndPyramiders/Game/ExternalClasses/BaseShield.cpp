/*===================================================================================*//**
	BaseShield
	
	Abstract class for a base shield.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseShield.h"
#include "Inventory.h"
#include "GameManager.h"


/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const string BaseShield::WOODEN_SHIELD_ICON_NAME = "shieldIcon.png";
const string BaseShield::WOODEN_SHIELD_IMAGE_NAME = "shield.png";
const float BaseShield::WOODEN_SHIELD_DAMAGE_MULT = 0.9f;
const float BaseShield::WOODEN_SHIELD_COOLDOWN_TIME = 0.5f;

const string BaseShield::SILVER_SHIELD_ICON_NAME = "shieldSilverIcon.png";
const string BaseShield::SILVER_SHIELD_IMAGE_NAME = "shieldSilver.png";
const float BaseShield::SILVER_SHIELD_DAMAGE_MULT = 0.7f;
const float BaseShield::SILVER_SHIELD_COOLDOWN_TIME = 0.4f;

const string BaseShield::GOLD_SHIELD_ICON_NAME = "shieldGoldIcon.png";
const string BaseShield::GOLD_SHIELD_IMAGE_NAME = "shieldGold.png";
const float BaseShield::GOLD_SHIELD_DAMAGE_MULT = 0.5f;
const float BaseShield::GOLD_SHIELD_COOLDOWN_TIME = 0.3f;

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
BaseShield::BaseShield(string imageName, string iconName, float damageMultiplier, float cooldownTime) :
	m_damageMultiplier{ damageMultiplier }, 
	m_blockCooldownTime{ cooldownTime },
	m_isBlocking{ false },
	m_offsetFromHolder{ Vector2(1, 0) }
{
	m_sprite = GameManager::getInstance()->createGameObject<SimpleSprite>(false, imageName, 0, 0, 0, 0);
	m_itemIcon = iconName;
	m_zIndex = 102;
}

std::shared_ptr<BaseItem> BaseShield::addSubclassToInventory()
{
	return m_inventory->setShield(shared_from_this());
}

bool BaseShield::use()
{
	auto willBlock = !m_isBlocking;

	if (willBlock)
	{
		onStart();
	}

	return willBlock;
}

void BaseShield::onStart()
{
	m_isBlocking = true;
	m_timeUntilNextBlock = m_blockCooldownTime;
	m_sprite->getTransform()->setScale(1);
	m_sprite->getTransform()->setZ(102);
}

void BaseShield::onUpdate(int ticks)
{
	updatePosition();
	updateBlock(ticks);
}

void BaseShield::onEnd()
{
	m_isBlocking = false;
	m_sprite->getTransform()->setScale(0);
}

bool BaseShield::isBlocking()
{
	return m_isBlocking;
}

int BaseShield::calculateRealDamage(int damage)
{
	return (int)((float)damage * m_damageMultiplier);
}

void BaseShield::setProperties(string imageName, string iconImageName, float damageMultiplier, float cooldownTime)
{
	m_damageMultiplier = damageMultiplier;
	m_blockCooldownTime = cooldownTime;
	m_sprite->destroy(m_sprite);
	m_sprite = GameManager::getInstance()->createGameObject<SimpleSprite>(false, imageName, 0, 0, 0, 0);
	m_itemIcon = iconImageName;
}

void BaseShield::updatePosition()
{
	if (owner() != nullptr)
	{
		/* Get the coordinates of the weapon before rotation. */
		float newX = owner()->getTransform()->getX() + m_offsetFromHolder.getX();
		float newY = owner()->getTransform()->getY() + m_offsetFromHolder.getY();

		/* Rotate the position about the weapon holder. */
		Vector2 newPosition = Vector2(newX, newY);
		newPosition.rotateFromOrigin(
			Vector2(owner()->getTransform()->getX(), owner()->getTransform()->getY()),
			owner()->getTransform()->getRotation()
		);

		m_sprite->getTransform()->setPosition(newPosition.getX(), newPosition.getY());

		/* Set the shield's rotation about its center. */
		m_sprite->getTransform()->setRotation(-owner()->getTransform()->getRotation());
	}
}

void BaseShield::updateBlock(int ticks)
{
	if (m_isBlocking)
	{
		m_timeUntilNextBlock -= (float)ticks / 1000.0f;

		if (m_timeUntilNextBlock <= 0)
		{
			onEnd();
		}
	}
}
