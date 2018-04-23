/*===================================================================================*//**
	BaseGreaves
	
	Abstract class for a base pair of greaves (leg armor).

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseGreaves.h"
#include "Inventory.h"
#include "CharacterController.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const std::string BaseGreaves::WOODEN_GREAVES_ICON_IMAGE_NAME = "greavesIcon.png";
const float BaseGreaves::WOODEN_GREAVES_COOLDOWN_TIME = 1.0f;
const float BaseGreaves::WOODEN_GREAVES_DASH_DURATION = 0.5f;
const float BaseGreaves::WOODEN_GREAVES_DASH_SPEED = 2.0f;

const std::string BaseGreaves::SILVER_GREAVES_ICON_IMAGE_NAME = "greavesSilverIcon.png";
const float BaseGreaves::SILVER_GREAVES_COOLDOWN_TIME = 0.9f;
const float BaseGreaves::SILVER_GREAVES_DASH_DURATION = 0.6f;
const float BaseGreaves::SILVER_GREAVES_DASH_SPEED = 2.5f;

const std::string BaseGreaves::GOLD_GREAVES_ICON_IMAGE_NAME = "greavesGoldIcon.png";
const float BaseGreaves::GOLD_GREAVES_COOLDOWN_TIME = 0.8f;
const float BaseGreaves::GOLD_GREAVES_DASH_DURATION = 0.7f;
const float BaseGreaves::GOLD_GREAVES_DASH_SPEED = 3.0f;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseGreaves::BaseGreaves(std::string iconImageName, float cooldownTime, float dashDuration, float dashSpeed) :
	m_cooldownTime{ cooldownTime }, 
	m_dashDuration{ dashDuration },
	m_dashSpeed{ dashSpeed },
	m_timeUntilNextUse{ 0 },
	m_isActive{ false }
{
	m_itemIcon = iconImageName;
	setupSprites(iconImageName);
	m_zIndex = 101;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseItem> BaseGreaves::addSubclassToInventory()
{
	return m_inventory->setGreaves(shared_from_this());
}

bool BaseGreaves::use()
{
	auto willActivate = !m_isActive;

	if (willActivate)
	{
		onStart();
	}

	return willActivate;
}

void BaseGreaves::onStart()
{
	m_isActive = true;
	m_timeUntilNextUse = m_cooldownTime;
	m_timeLeftInDash = m_dashDuration;
}

void BaseGreaves::onUpdate(int ticks)
{
	updateEffect(ticks);
}

void BaseGreaves::onEnd()
{
	m_isActive = false;
}

void BaseGreaves::updateEffect(int ticks)
{
	if (m_isActive)
	{
		effect(ticks);
		m_timeUntilNextUse -= (float)ticks / 1000.0f;

		if (m_timeUntilNextUse <= 0)
		{
			onEnd();
		}
	}
}

void BaseGreaves::effect(int ticks)
{
	if (m_timeLeftInDash > 0)
	{
		auto dashRotation = owner()->getTransform()->getRotation();
		auto dashAmount = ((float)ticks / 1000.0f) * m_dashSpeed;

		auto dashDirection = Vector2(1, 0);
		dashDirection.rotate(dashRotation);
		Vector2* pDashDuration = dashDirection * dashAmount;

		owner()->getComponent<CharacterController>()->move(*pDashDuration);
		m_timeLeftInDash -= (float)ticks / 1000.0f;
	}
}

void BaseGreaves::setProperties(std::string iconImageName, float cooldownTime, float dashDuration, float dashSpeed)
{
	m_itemIcon = iconImageName;
	m_cooldownTime = cooldownTime;
	m_dashDuration = dashDuration;
	m_dashSpeed = dashSpeed;
}

/*----------------------------------------------------------------------------------------
| Setup Sprites and Animations
----------------------------------------------------------------------------------------*/
void BaseGreaves::setupSprites(std::string identifier)
{
	spriteInfo = std::make_shared<ComplexSpriteInfo>();

	if (identifier == BaseGreaves::WOODEN_GREAVES_ICON_IMAGE_NAME)
	{
		addSprite("Player/Walk/greaves.png", "walk", 9, 4);
		addAnimation("walk", "WalkUp", 1, 8);
		addAnimation("walk", "WalkLeft", 10, 17);
		addAnimation("walk", "WalkDown", 19, 26);
		addAnimation("walk", "WalkRight", 28, 35);
		addAnimation("walk", "IdleUp", 0, 0);
		addAnimation("walk", "IdleLeft", 9, 9);
		addAnimation("walk", "IdleDown", 18, 18);
		addAnimation("walk", "IdleRight", 27, 27);

		addSprite("Player/Attack/Bow/greaves.png", "shoot", 13, 4);
		addAnimation("shoot", "ShootUp", 1, 12);
		addAnimation("shoot", "ShootLeft", 14, 25);
		addAnimation("shoot", "ShootDown", 27, 38);
		addAnimation("shoot", "ShootRight", 40, 51);
		addAnimation("shoot", "IdleUp", 0, 0);
		addAnimation("shoot", "IdleLeft", 13, 13);
		addAnimation("shoot", "IdleDown", 26, 26);
		addAnimation("shoot", "IdleRight", 39, 39);

		addSprite("Player/Attack/Melee/greaves.png", "slash", 6, 4);
		addAnimation("slash", "SlashUp", 1, 5);
		addAnimation("slash", "SlashLeft", 7, 11);
		addAnimation("slash", "SlashDown", 13, 17);
		addAnimation("slash", "SlashRight", 19, 23);
		addAnimation("slash", "IdleUp", 0, 0);
		addAnimation("slash", "IdleLeft", 6, 6);
		addAnimation("slash", "IdleDown", 12, 12);
		addAnimation("slash", "IdleRight", 18, 18);
	}
	else if (identifier == BaseGreaves::SILVER_GREAVES_ICON_IMAGE_NAME)
	{
		addSprite("Player/Walk/greaves.png", "walk", 9, 4);
		addAnimation("walk", "WalkUp", 1, 8);
		addAnimation("walk", "WalkLeft", 10, 17);
		addAnimation("walk", "WalkDown", 19, 26);
		addAnimation("walk", "WalkRight", 28, 35);
		addAnimation("walk", "IdleUp", 0, 0);
		addAnimation("walk", "IdleLeft", 9, 9);
		addAnimation("walk", "IdleDown", 18, 18);
		addAnimation("walk", "IdleRight", 27, 27);

		addSprite("Player/Attack/Bow/greaves.png", "shoot", 13, 4);
		addAnimation("shoot", "ShootUp", 1, 12);
		addAnimation("shoot", "ShootLeft", 14, 25);
		addAnimation("shoot", "ShootDown", 27, 38);
		addAnimation("shoot", "ShootRight", 40, 51);
		addAnimation("shoot", "IdleUp", 0, 0);
		addAnimation("shoot", "IdleLeft", 13, 13);
		addAnimation("shoot", "IdleDown", 26, 26);
		addAnimation("shoot", "IdleRight", 39, 39);

		addSprite("Player/Attack/Melee/greaves.png", "slash", 6, 4);
		addAnimation("slash", "SlashUp", 1, 5);
		addAnimation("slash", "SlashLeft", 7, 11);
		addAnimation("slash", "SlashDown", 13, 17);
		addAnimation("slash", "SlashRight", 19, 23);
		addAnimation("slash", "IdleUp", 0, 0);
		addAnimation("slash", "IdleLeft", 6, 6);
		addAnimation("slash", "IdleDown", 12, 12);
		addAnimation("slash", "IdleRight", 18, 18);
	}
	else if (identifier == BaseGreaves::GOLD_GREAVES_ICON_IMAGE_NAME)
	{
		addSprite("Player/Atlas/goldGreaves.png", "walk", 13, 21);
		addSprite("Player/Atlas/goldGreaves.png", "shoot", 13, 21);
		addSprite("Player/Atlas/goldGreaves.png", "slash", 13, 21);

		addAnimation("walk", "WalkUp", 104, 112);
		addAnimation("walk", "WalkLeft", 117, 125);
		addAnimation("walk", "WalkDown", 130, 138);
		addAnimation("walk", "WalkRight", 143, 151);
		addAnimation("walk", "IdleUp", 104, 104);
		addAnimation("walk", "IdleLeft", 117, 117);
		addAnimation("walk", "IdleDown", 130, 130);
		addAnimation("walk", "IdleRight", 143, 143);

		addAnimation("shoot", "ShootUp", 208, 220);
		addAnimation("shoot", "ShootLeft", 221, 233);
		addAnimation("shoot", "ShootDown", 234, 246);
		addAnimation("shoot", "ShootRight", 247, 259);
		addAnimation("shoot", "IdleUp", 208, 208);
		addAnimation("shoot", "IdleLeft", 221, 221);
		addAnimation("shoot", "IdleDown", 234, 234);
		addAnimation("shoot", "IdleRight", 247, 247);

		addAnimation("slash", "SlashUp", 156, 161);
		addAnimation("slash", "SlashLeft", 169, 174);
		addAnimation("slash", "SlashDown", 182, 187);
		addAnimation("slash", "SlashRight", 195, 200);
		addAnimation("slash", "IdleUp", 156, 156);
		addAnimation("slash", "IdleLeft", 169, 169);
		addAnimation("slash", "IdleDown", 182, 182);
		addAnimation("slash", "IdleRight", 195, 195);
	}
}