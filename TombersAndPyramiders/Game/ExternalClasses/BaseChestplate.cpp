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
	Resource Management
----------------------------------------------------------------------------------------*/
BaseChestplate::BaseChestplate(float damageMultiplier) :
	m_damageMultiplier{ damageMultiplier }
{

}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
int BaseChestplate::calculateRealDamage(int damage)
{
	return (int)((float)damage * m_damageMultiplier);
}

std::shared_ptr<BaseItem> BaseChestplate::addSubclassToInventory()
{
	return m_inventory->setChestplate(shared_from_this());
}
