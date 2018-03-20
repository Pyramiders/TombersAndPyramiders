/*===================================================================================*//**
	BaseWeapon
	
	Abstract class for a base weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseWeapon.h"
#include "Inventory.h"
#include <memory>

/*----------------------------------------------------------------------------------------
	Class Fields
----------------------------------------------------------------------------------------*/
const float BaseWeapon::CRITICAL_HIT_DAMAGE_MULTIPLIER = 2.0f;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseWeapon::BaseWeapon(int damage, float criticalHitChance, float attackCooldownTime) :
	m_damage{ damage }, 
	m_criticalHitChance{ criticalHitChance },
	m_attackCooldownTime{ attackCooldownTime }, 
	m_isAttacking{ false }
{
	if (m_criticalHitChance < 0)
	{
		throw std::invalid_argument("BaseWeapon::BaseWeapon(): m_criticalHitChanceMust be non-negative.");
	}
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseItem> BaseWeapon::addSubclassToInventory()
{
	return m_inventory->setWeapon(shared_from_this());
}

bool BaseWeapon::isAttacking()
{
	return m_isAttacking;
}
