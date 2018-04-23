/*===================================================================================*//**
	BaseHelmet
	
	Abstract class for a base helmet.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include <stdexcept>
#include "BaseHelmet.h"
#include "Inventory.h"
#include "Randomize.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const std::string BaseHelmet::WOODEN_HELMET_ICON_IMAGE = "helmetIcon.png";
const float BaseHelmet::WOODEN_HELMET_CRITICAL_RESIST_CHANCE = 0.05f;
const std::string BaseHelmet::SILVER_HELMET_ICON_IMAGE = "helmetSilverIcon.png";
const float BaseHelmet::SILVER_HELMET_CRITICAL_RESIST_CHANCE = 0.2f;
const std::string BaseHelmet::GOLD_HELMET_ICON_IMAGE = "helmetGoldIcon.png";
const float BaseHelmet::GOLD_HELMET_CRITICAL_RESIST_CHANCE = 0.5f;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseHelmet::BaseHelmet(std::string iconImageName, float criticalResistChance) :
	m_criticalResistChance{ criticalResistChance }
{
	if (m_criticalResistChance < 0)
	{
		throw std::invalid_argument("BaseHelmet::BaseHelmet(): m_criticalResistChance must be non-negative.");
	}

	m_itemIcon = iconImageName;

	setupSprites(iconImageName);
	m_zIndex = 101;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
bool BaseHelmet::doesAvoidCriticalHit()
{
	return (Randomize::RandomFloat(0, 1) < m_criticalResistChance);
}

void BaseHelmet::setProperties(std::string iconImageName, float criticalResistChance)
{
	m_itemIcon = iconImageName;
	m_criticalResistChance = criticalResistChance;
}

std::shared_ptr<BaseItem> BaseHelmet::addSubclassToInventory()
{
	return m_inventory->setHelmet(shared_from_this());
}

/*----------------------------------------------------------------------------------------
| Setup Sprites and Animations
----------------------------------------------------------------------------------------*/
void BaseHelmet::setupSprites(std::string identifier)
{
	spriteInfo = std::make_shared<ComplexSpriteInfo>();

	if (identifier == BaseHelmet::WOODEN_HELMET_ICON_IMAGE)
	{
		addSprite("Player/Atlas/helmet.png", "walk", 13, 21);
		addSprite("Player/Atlas/helmet.png", "shoot", 13, 21);
		addSprite("Player/Atlas/helmet.png", "slash", 13, 21);

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
	else if (identifier == BaseHelmet::SILVER_HELMET_ICON_IMAGE)
	{
		//addSprite("Player/Atlas/helmet_silver.png", "walk", 13, 21);
		//addSprite("Player/Atlas/helmet_silver.png", "shoot", 13, 21);
		//addSprite("Player/Atlas/helmet_silver.png", "slash", 13, 21);

		addSprite("Player/Atlas/helmet.png", "walk", 13, 21);
		addSprite("Player/Atlas/helmet.png", "shoot", 13, 21);
		addSprite("Player/Atlas/helmet.png", "slash", 13, 21);

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
	else if (identifier == BaseHelmet::GOLD_HELMET_ICON_IMAGE)
	{
		//addSprite("Player/Atlas/helmet_gold.png", "walk", 13, 21);
		//addSprite("Player/Atlas/helmet_gold.png", "shoot", 13, 21);
		//addSprite("Player/Atlas/helmet_gold.png", "slash", 13, 21);

		addSprite("Player/Atlas/goldHelmet.png", "walk", 13, 21);
		addSprite("Player/Atlas/goldHelmet.png", "shoot", 13, 21);
		addSprite("Player/Atlas/goldHelmet.png", "slash", 13, 21);

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