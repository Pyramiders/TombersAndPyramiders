/*===================================================================================*//**
	Damageable
	
	Abstract class for something that has HP, can be damaged, and can "die".

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include <stdexcept>
#include <algorithm>
#include "Damageable.h"
#include "SpawnManager.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
Damageable::Damageable(int maxHealth) :
	m_maxHealth{ maxHealth }, m_health{ maxHealth }
{
	if (maxHealth < 1)
	{
		throw std::invalid_argument("Damageable::Damageable: maxHealth must be greater than zero.");
	}
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
int Damageable::getHealth()
{
	return m_health;
}

void Damageable::setHealth(int health)
{
	/* Cap min = 0 and max = max health. */
	m_health = std::min(std::max(health, 0), m_maxHealth);
	 
}

void Damageable::takeDamage(int damage)
{
	setHealth(getHealth() - damage);
}
