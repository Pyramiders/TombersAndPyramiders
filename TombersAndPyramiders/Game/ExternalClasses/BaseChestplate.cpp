/*===================================================================================*//**
	BaseChestplate
	
	Abstract class for a base chestplate

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseChestplate.h"
#include "Inventory.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const std::string BaseChestplate::WOODEN_CHESTPLATE_ICON_IMAGE_NAME = "WoodenChestplateIcon.png";
const float BaseChestplate::WOODEN_CHESTPLATE_DAMAGE_MULTIPLIER = 0.95;
const std::string BaseChestplate::SILVER_CHESTPLATE_ICON_IMAGE_NAME = "SilverChestplateIcon.png";
const float BaseChestplate::SILVER_CHESTPLATE_DAMAGE_MULTIPLIER = 0.85;
const std::string BaseChestplate::GOLD_CHESTPLATE_ICON_IMAGE_NAME = "GoldChestplateIcon.png";
const float BaseChestplate::GOLD_CHESTPLATE_DAMAGE_MULTIPLIER = 0.75;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseChestplate::BaseChestplate(std::string iconImageName, float damageMultiplier) :
	m_damageMultiplier{ damageMultiplier }
{
	m_itemIcon = iconImageName;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
int BaseChestplate::calculateRealDamage(int damage)
{
	return (int)((float)damage * m_damageMultiplier);
}

void BaseChestplate::setProperties(std::string iconImageName, float damageMultiplier)
{
	m_itemIcon = iconImageName;
	m_damageMultiplier = damageMultiplier;
}

std::shared_ptr<BaseItem> BaseChestplate::addSubclassToInventory()
{
	return m_inventory->setChestplate(shared_from_this());
}
