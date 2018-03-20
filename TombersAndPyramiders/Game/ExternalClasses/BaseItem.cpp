/*===================================================================================*//**
	BaseItem
	
	Abstract class for an item that can be carried in an Inventory.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseItem.h"
#include "Inventory.h"

/*----------------------------------------------------------------------------------------
	Class Fields
----------------------------------------------------------------------------------------*/
RandomHelper BaseItem::s_random = RandomHelper();

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseItem> BaseItem::addToInventory(Inventory* inventory)
{
	m_inventory = inventory;

	if (m_inventory != nullptr)
	{
		return addSubclassToInventory();
	}
	return nullptr;
}

GameObject* BaseItem::owner()
{
	return (m_inventory == nullptr) ? nullptr : m_inventory->getGameObject();
}

std::string BaseItem::getItemIcon()
{
	return m_itemIcon;
}