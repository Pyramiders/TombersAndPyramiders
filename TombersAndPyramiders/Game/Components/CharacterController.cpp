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
#include "Rigidbody.h"
#include "Character.h"
#include "BaseMeleeWeapon.h"
#include "BaseProjectileWeapon.h"
#include "Collider.h"
#include "SpawnManager.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const int CharacterController::DEFAULT_CHARACTER_MAX_HP = 100;
const Vector2 CharacterController::DEFAULT_CHARACTER_MOVEMENT_SPEED = Vector2(0.25, 0.25);

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

	Character* character = dynamic_cast<Character*>(gameObject);
	if (character != nullptr)
	{
		m_character = std::shared_ptr<Character>(character);
	}
	m_boxCollider = gameObject->addComponent<BoxCollider>(gameObject, 1, 1);
	//m_boxCollider = gameObject->addComponent<BoxCollider>(gameObject, gameObject->getTransform()->getScale(), gameObject->getTransform()->getScale());
	m_rigidbody = gameObject->addComponent<Rigidbody>(gameObject, m_boxCollider.get());
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void CharacterController::onStart()
{
	//m_boxCollider = gameObject->addComponent<BoxCollider>(gameObject, 10, 10);
	//m_boxCollider = gameObject->addComponent<BoxCollider>(gameObject, gameObject->getTransform()->getScale(), gameObject->getTransform()->getScale());
	//m_rigidbody = gameObject->addComponent<Rigidbody>(gameObject, m_boxCollider.get());
}

void CharacterController::onUpdate(int ticks)
{
	m_pilot.get()->onUpdate(ticks);

	updateWeapon(ticks);
	updateShield(ticks);
	updateGreaves(ticks);
}

void CharacterController::move(Vector2 delta)
{
	//std::cout << "X: " << delta.getX() << ", Y: " << delta.getY() << "\n";
	delta.setX(delta.getX() * m_movementSpeed.getX());
	delta.setY(delta.getY() * m_movementSpeed.getY());

	if (delta.getMagnitude() == 0)
	{
		m_character->endRunAnimation();
	} else 
	{
		m_character->playRunAnimation();
		//gameObject->getTransform()->setRotation(delta.getRotationInDegrees());
	}

	gameObject->getTransform()->addTranslation(delta.getX(), delta.getY());
	m_rigidbody->setVelocity(delta);
}

void CharacterController::useWeapon()
{
	std::shared_ptr<BaseWeapon> weapon = m_inventory->getWeapon();
	if (weapon != nullptr)
	{
		weapon->use(); //What if this returned a bool for whether the attack fired or not? So the rest didn't fire for just trying to call useWeapon and let us let weapons determine then things likecooldown
		//m_inventory->getWeapon()->use();
		 
		//dynamic_cast<BaseMeleeWeapon>(weapon);
		m_character->playMeleeAttackAnimation();
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

std::shared_ptr<WorldItem> CharacterController::trySwapItem()
{
	std::shared_ptr<BoxCollider> myCollider = gameObject->getComponent<BoxCollider>();
	if (myCollider != nullptr && myCollider->collisionDetected()) {
		std::vector<GameObject*> collidedObjects = myCollider->getColliders();
		for (int i = 0; i < collidedObjects.size(); i++)
		{
			WorldItem* worldItem = dynamic_cast<WorldItem*>(collidedObjects[i]);

			if (worldItem != nullptr) 
			{
				float oldX = worldItem->getTransform()->getX();
				float oldY = worldItem->getTransform()->getY();

				std::shared_ptr<BaseItem> extractedItem = worldItem->pickupItem();

				std::shared_ptr<BaseItem> removedItem = m_inventory->addItem(extractedItem);
				if (removedItem != nullptr) {
					return SpawnManager::getInstance()->generateWorldItem(oldX, oldY, removedItem);
				}

				break;
			}
		}
	}
	return nullptr;
}
