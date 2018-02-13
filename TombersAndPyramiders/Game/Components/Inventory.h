/*===================================================================================*//**
	Inventory
	
	A component representing a collection of items owned by a GameObject.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include <memory>
#include "Component.h"
#include "BaseWeapon.h"
#include "BaseShield.h"
#include "BaseHelmet.h"
#include "BaseChestplate.h"
#include "BaseGreaves.h"

/*========================================================================================
	Inventory	
========================================================================================*/
class Inventory : public Component
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
    private:
		std::shared_ptr<BaseWeapon> m_weapon;
		std::shared_ptr<BaseShield> m_shield;
		std::shared_ptr<BaseHelmet> m_helmet;
		std::shared_ptr<BaseChestplate> m_chestplate;
		std::shared_ptr<BaseGreaves> m_greaves;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        explicit Inventory() = delete;

		/**
			Initializes inventory with nullptr equipment.
		*/
		explicit Inventory(GameObject* parentGameobject);

		explicit Inventory(GameObject* parentGameobject, std::shared_ptr<BaseWeapon> weapon, std::shared_ptr<BaseShield> shield, std::shared_ptr<BaseHelmet> helmet,
			std::shared_ptr<BaseChestplate> chestplate, std::shared_ptr<BaseGreaves> greaves);

	/*----------------------------------------------------------------------------------------
		Instance Getter Methods
    ----------------------------------------------------------------------------------------*/
    public:
        std::shared_ptr<BaseWeapon> getWeapon();
		std::shared_ptr<BaseShield> getShield();
		std::shared_ptr<BaseHelmet> getHelmet();
		std::shared_ptr<BaseChestplate> getChestplate();
		std::shared_ptr<BaseGreaves> getGreaves();
    
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
    public:
		/**
			DO NOT CALL THESE METHODS.
			CALL INVENTORY.ADDITEM() INSTEAD.
		*/
		std::shared_ptr<BaseWeapon> setWeapon(std::shared_ptr<BaseWeapon> weapon);
		std::shared_ptr<BaseShield> setShield(std::shared_ptr<BaseShield> shield);
		std::shared_ptr<BaseHelmet> setHelmet(std::shared_ptr<BaseHelmet> helmet);
		std::shared_ptr<BaseChestplate> setChestplate(std::shared_ptr<BaseChestplate> chestplate);
		std::shared_ptr<BaseGreaves> setGreaves(std::shared_ptr<BaseGreaves> greaves);

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		/**
			Adds an item to the inventory.
			addItem() will resolve the item's type and add or set it appropriately.
			If addItem replaced a previous item, it is removed form the inventory and returned, or nullptr if nothing is replaced
		*/
		std::shared_ptr<BaseItem> addItem(std::shared_ptr<BaseItem> item);
		void onStart();
		void onUpdate(int ticks);
		void onEnd();

    private:

};
