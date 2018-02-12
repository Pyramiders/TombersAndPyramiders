/*===================================================================================*//**
	CharacterController
	
	Abstract class for a component that controls the actions of an agent.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "CharacterController.h"
#include "BaseController.h"
#include "BasePilot.h"
#include "Vector2.h"
#include "Component.h"
#include "GameObject.h"
#include "Inventory.h"
#include "BaseWeapon.h"
#include "BaseShield.h"
#include "BaseGreaves.h"
#include "PlayerCharacter.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const int CharacterController::DEFAULT_PLAYER_MAX_HP = 100;
const Vector2 CharacterController::DEFAULT_PLAYER_MOVEMENT_SPEED = Vector2(1, 1);

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
CharacterController::CharacterController(GameObject* parentGameobject, Inventory* inventory,
										 BasePilot* pilot, int maxHealth, Vector2 movementSpeed) :
	BaseController(parentGameobject, pilot), Damageable(maxHealth),
	m_inventory{ inventory },
	m_movementSpeed{ movementSpeed }
{
	if (m_inventory == nullptr)
	{
		throw std::invalid_argument("CharacterController::CharacterController(): m_inventory cannot be null.");
	}

	PlayerCharacter* player = dynamic_cast<PlayerCharacter*>(gameObject);
	if (player != nullptr) 
	{
		m_playerCharacter = std::shared_ptr<PlayerCharacter>(player);
	}
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void CharacterController::onUpdate(int ticks)
{
	m_pilot.get()->onUpdate(ticks);

	updateWeapon(ticks);
	updateShield(ticks);
	updateGreaves(ticks);
}

void CharacterController::move(Vector2 delta)
{
	delta.setX(delta.getX() * m_movementSpeed.getX());
	delta.setY(delta.getY() * m_movementSpeed.getY());

	if (delta.getMagnitude() == 0)
	{
		m_playerCharacter->endRunAnimation();
	} else 
	{
		m_playerCharacter->playRunAnimation();
		gameObject->getTransform()->setRotation(delta.getRotationInDegrees());
	}

	gameObject->getTransform()->addTranslation(delta.getX(), delta.getY());
}

void CharacterController::useWeapon()
{
	if (m_inventory->getWeapon() != nullptr)
	{
		m_inventory->getWeapon()->use();
	}
}

void CharacterController::updateWeapon(int ticks)
{
	if (m_inventory->getWeapon() != nullptr)
	{
		m_inventory->getWeapon()->onUpdate(ticks);
	}
}

void CharacterController::updateShield(int ticks)
{
	if (m_inventory->getShield() != nullptr)
	{
		m_inventory->getShield()->onUpdate(ticks);
	}
}

void CharacterController::updateGreaves(int ticks)
{
	if (m_inventory->getGreaves() != nullptr)
	{
		m_inventory->getGreaves()->onUpdate(ticks);
	}
}

void CharacterController::death()
{

}
