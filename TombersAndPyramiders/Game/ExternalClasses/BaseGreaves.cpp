/*===================================================================================*//**
	BaseGreaves
	
	Abstract class for a base pair of greaves (leg armor).

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseGreaves.h"
#include "Inventory.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseGreaves::BaseGreaves(float cooldownTime) :
	m_cooldownTime{ cooldownTime }, 
	m_timeUntilNextUse{ 0 },
	m_isActive{ false }
{}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
std::shared_ptr<BaseItem> BaseGreaves::addSubclassToInventory()
{
	return m_inventory->setGreaves(shared_from_this());
}

bool BaseGreaves::use()
{
	auto willActivate = !m_isActive;

	if (willActivate)
	{
		onStart();
	}

	return willActivate;
}

void BaseGreaves::onStart()
{
	m_isActive = true;
	m_timeUntilNextUse = m_cooldownTime;
}

void BaseGreaves::onUpdate(int ticks)
{
	updateEffect(ticks);
}

void BaseGreaves::onEnd()
{
	m_isActive = false;
}

void BaseGreaves::updateEffect(int ticks)
{
	if (m_isActive)
	{
		effect(ticks);
		m_timeUntilNextUse -= (float)ticks / 1000.0f;

		if (m_timeUntilNextUse <= 0)
		{
			onEnd();
		}
	}
}
