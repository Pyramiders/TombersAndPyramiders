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
const std::string BaseGreaves::WOODEN_GREAVES_ICON_IMAGE_NAME = "WoodenGreavesIcon.png";
const float BaseGreaves::WOODEN_GREAVES_COOLDOWN_TIME = 1.0f;
const float BaseGreaves::WOODEN_GREAVES_DASH_DURATION = 0.5f;
const float BaseGreaves::WOODEN_GREAVES_DASH_SPEED = 40.0f;

const std::string BaseGreaves::SILVER_GREAVES_ICON_IMAGE_NAME = "SilverGreavesIcon.png";
const float BaseGreaves::SILVER_GREAVES_COOLDOWN_TIME = 0.9f;
const float BaseGreaves::SILVER_GREAVES_DASH_DURATION = 0.6f;
const float BaseGreaves::SILVER_GREAVES_DASH_SPEED = 40.0f;

const std::string BaseGreaves::GOLD_GREAVES_ICON_IMAGE_NAME = "GoldGreavesIcon.png";
const float BaseGreaves::GOLD_GREAVES_COOLDOWN_TIME = 0.8f;
const float BaseGreaves::GOLD_GREAVES_DASH_DURATION = 0.7f;
const float BaseGreaves::GOLD_GREAVES_DASH_SPEED = 40.0f;

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
