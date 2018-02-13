/*===================================================================================*//**
	BaseItem
	
	Abstract class for an item that can be carried in an Inventory.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

#include <memory>
#include <string>

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
		Instance Fields
	----------------------------------------------------------------------------------------*/
	public:
		static const float TICKS_PER_SECOND; /* Ha ha, I have no other place for this. */

	protected:
		Inventory* m_inventory;
		std::string m_itemIcon;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseItem() = default;

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

	protected:
		/**
			Adds a subclass item to the inventory.

			This should only be called after checking that m_inventory is NOT null.
		*/
		virtual std::shared_ptr<BaseItem> addSubclassToInventory() = 0;
};
