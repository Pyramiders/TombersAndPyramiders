/*===================================================================================*//**
	BaseItem
	
	Abstract class for an item that can be carried in an Inventory.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

#include <memory>
#include <string>
#include "ComplexSprite.h"

/*========================================================================================
	Dependencies	
========================================================================================*/
class Inventory;
class GameObject;

/*========================================================================================
	BaseItem	
========================================================================================*/
class BaseItem
{
	/*----------------------------------------------------------------------------------------
		Class Fields
	----------------------------------------------------------------------------------------*/
	protected:

	/*----------------------------------------------------------------------------------------
		Instance Fields
	----------------------------------------------------------------------------------------*/
	protected:
		Inventory* m_inventory;
		std::string m_itemIcon;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseItem();
		virtual ~BaseItem() {};

    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
	public:
		/**
			Adds this item to the given inventory.
			
			Sets the item's m_inventory field and calls addSubclassToInventory(), which 
			should be overriden by subclasses to add themselves to the inventory.
		*/
		std::shared_ptr<BaseItem> addToInventory(Inventory* inventory);

		std::string getItemIcon();

		/**
			Returns a reference to the GameObject that owns the Inventory component this 
			item is held by.
		*/
		virtual GameObject* owner();

	/*----------------------------------------------------------------------------------------
	Sprite/Animation Setup
	----------------------------------------------------------------------------------------*/
	public:
		/**
			Creates the data that need to be fed to ComplexSprite during setup.
		*/
		std::shared_ptr<ComplexSpriteInfo> spriteInfo;
		void addSprite(std::string filePath, std::string spriteName, int columns, int rows);
		void addAnimation(std::string spriteName, std::string animationName, int frameStart, int frameEnd);
		virtual void setupSprites();
		float m_zIndex;

	protected:
		/**
			Adds a subclass item to the inventory.

			This should only be called after checking that m_inventory is NOT null.
		*/
		virtual std::shared_ptr<BaseItem> addSubclassToInventory() = 0;
};
