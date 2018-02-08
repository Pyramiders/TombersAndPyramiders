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
		std::unique_ptr<BaseWeapon> m_weapon;
		std::unique_ptr<BaseShield> m_shield;
		std::unique_ptr<BaseHelmet> m_helmet;
		std::unique_ptr<BaseChestplate> m_chestplate;
		std::unique_ptr<BaseGreaves> m_greaves;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        explicit Inventory() = delete;

		/**
			Initializes inventory with nullptr equipment.
		*/
		explicit Inventory(GameObject* gameobject);

		explicit Inventory(GameObject* gameobject, BaseWeapon* weapon, BaseShield* shield, BaseHelmet* helmet,
			BaseChestplate* chestplate, BaseGreaves* greaves);

	/*----------------------------------------------------------------------------------------
		Instance Getter Methods
    ----------------------------------------------------------------------------------------*/
    public:
        BaseWeapon& getWeapon();
		BaseShield& getShield();
		BaseHelmet& getHelmet();
		BaseChestplate& getChestplate();
		BaseGreaves& getGreaves();
    
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
    public:
		void setWeapon(BaseWeapon* weapon);
		void setShield(BaseShield* shield);
		void setHelmet(BaseHelmet* helmet);
		void setChestplate(BaseChestplate* chestplate);
		void setGreaves(BaseGreaves* greaves);

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		/**
			Adds an item to the inventory.
			addItem() will resolve the item's type and add or set it appropriately.
		*/
		void addItem(BaseItem* item);
		void onStart();
		void onUpdate(int ticks);
		void onEnd();

    private:

};
