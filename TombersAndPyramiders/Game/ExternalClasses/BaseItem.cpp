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
#include "Randomize.h"

/*----------------------------------------------------------------------------------------
	Class Fields
----------------------------------------------------------------------------------------*/
BaseItem::BaseItem()
{
}

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

/*----------------------------------------------------------------------------------------
Sprite/Animation Setup
----------------------------------------------------------------------------------------*/
void BaseItem::addSprite(std::string filePath, std::string spriteName, int rows, int columns)
{
	spriteInfo->addSprite(filePath, spriteName, rows, columns);
}
void BaseItem::addAnimation(std::string spriteName, std::string animationName, int frameStart, int frameEnd)
{
	spriteInfo->addAnimation(spriteName, animationName, frameStart, frameEnd);
}
void BaseItem::setupSprites()
{
	spriteInfo = std::make_shared<ComplexSpriteInfo>();
}