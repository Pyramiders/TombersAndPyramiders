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
const std::string BaseHelmet::WOODEN_HELMET_ICON_IMAGE = "WoodenHelmetIcon.png";
const float BaseHelmet::WOODEN_HELMET_CRITICAL_RESIST_CHANCE = 0.05f;
const std::string BaseHelmet::SILVER_HELMET_ICON_IMAGE = "SilverHelmetIcon.png";
const float BaseHelmet::SILVER_HELMET_CRITICAL_RESIST_CHANCE = 0.2f;
const std::string BaseHelmet::GOLD_HELMET_ICON_IMAGE = "GoldHelmetIcon.png";
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
