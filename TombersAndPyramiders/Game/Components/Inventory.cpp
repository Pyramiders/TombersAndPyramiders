/*===================================================================================*//**
	Inventory
	
	A component representing a collection of items owned by a GameObject.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Inventory.h"
#include "BaseItem.h"
#include "BaseWeapon.h"
#include "BaseShield.h"
#include "BaseHelmet.h"
#include "BaseChestplate.h"
#include "BaseGreaves.h"
#include "GameObject.h"
#include "Character.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
Inventory::Inventory(GameObject* parentGameobject) :
	Inventory(parentGameobject, nullptr, nullptr, nullptr, nullptr, nullptr)
{}

Inventory::Inventory(GameObject* parentGameobject, std::shared_ptr<BaseWeapon> weapon, std::shared_ptr<BaseShield> shield, std::shared_ptr<BaseHelmet> helmet,
	std::shared_ptr<BaseChestplate> chestplate, std::shared_ptr<BaseGreaves> greaves) :
	Component(parentGameobject),
	m_weapon{ weapon },
	m_shield{ shield },
	m_helmet{ helmet },
	m_chestplate{ chestplate },
	m_greaves{ greaves }
{}

/*----------------------------------------------------------------------------------------
	Instance Getter Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseWeapon> Inventory::getWeapon()
{
	return m_weapon;
}


std::shared_ptr<BaseShield> Inventory::getShield()
{
	return m_shield;
}

std::shared_ptr<BaseHelmet> Inventory::getHelmet()
{
	return m_helmet;
}

std::shared_ptr<BaseChestplate> Inventory::getChestplate()
{
	return m_chestplate;
}

std::shared_ptr<BaseGreaves> Inventory::getGreaves()
{
	return m_greaves;
}

/*----------------------------------------------------------------------------------------
	Instance Setter Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseWeapon> Inventory::setWeapon(std::shared_ptr<BaseWeapon> weapon)
{
	auto old = m_weapon;
	m_weapon = weapon;
	m_weapon->setOwnerId(gameObject->getId());
	return old;
}



std::shared_ptr<BaseShield> Inventory::setShield(std::shared_ptr<BaseShield> shield)
{
	auto old = m_shield;
	m_shield = shield;
	return old;
}

std::shared_ptr<BaseHelmet> Inventory::setHelmet(std::shared_ptr<BaseHelmet> helmet)
{
	auto old = m_helmet;
	m_helmet = helmet;
	return old;
}

std::shared_ptr<BaseChestplate> Inventory::setChestplate(std::shared_ptr<BaseChestplate> chestplate)
{
	auto old = m_chestplate;
	m_chestplate = chestplate;
	return old;
}

std::shared_ptr<BaseGreaves> Inventory::setGreaves(std::shared_ptr<BaseGreaves> greaves)
{
	auto old = m_greaves;
	m_greaves = greaves;
	return old;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseItem> Inventory::addItem(std::shared_ptr<BaseItem> item)
{
	auto itemRemoved = item->addToInventory(this);

	auto owner = (Character *)getGameObject();

	//Character *owner = dynamic_cast<Character*>(getGameObject());
	if (owner != nullptr)
	{
		owner->updateInventory(false, itemRemoved);
		owner->updateInventory(true, item);
	}

	return itemRemoved;
}


void Inventory::onStart()
{};

void Inventory::onUpdate(int ticks)
{};

void Inventory::onEnd()
{};
