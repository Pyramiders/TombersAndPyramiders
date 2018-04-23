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
#include "AudioManager.h"
#include "GameManager.h"
#include "Invokable.h"
#include "BasePossessableController.h"
#include "Sender.h"
#include "GhostPilot.h"
#include "NetworkCharacter.h"
#include "PlayerPilot.h"
#include "Receiver.h"
#include "MessageManager.h"
#include "GeneratorManager.h"
#include <sstream>

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const int CharacterController::DEFAULT_CHARACTER_MAX_HP = 100;
const Vector2 CharacterController::DEFAULT_CHARACTER_MOVEMENT_SPEED = Vector2(3, 3);

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
	m_boxCollider = gameObject->addComponent<BoxCollider>(gameObject, gameObject->getTransform()->getScale(), gameObject->getTransform()->getScale());
	m_rigidbody = gameObject->addComponent<Rigidbody>(gameObject, m_boxCollider.get());
	m_audioSource = gameObject->addComponent<AudioSource>(gameObject);
	if (dynamic_cast<PlayerPilot*>(m_pilot.get()) != nullptr)
	{
		m_audioListener = gameObject->addComponent<AudioListener>(gameObject);
	}
	level = 0;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void CharacterController::onStart()
{}

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
		m_character->endRunAnimation();
	} else 
	{
		m_character->playRunAnimation();
		gameObject->getTransform()->setRotation(delta.getRotationInDegrees());
	}

	gameObject->getTransform()->addTranslation(delta.getX(), delta.getY());
	m_rigidbody->setVelocity(delta);
}

void CharacterController::useWeapon()
{
	std::shared_ptr<BaseWeapon> weapon = m_inventory->getWeapon();
	std::shared_ptr<BaseShield> shield = m_inventory->getShield();

	if (weapon != nullptr && 
		(shield == nullptr || !shield->isBlocking()))
	{
		if (weapon->use())
		{
			std::shared_ptr<BaseMeleeWeapon> melee = dynamic_pointer_cast<BaseMeleeWeapon>(weapon);
			if (melee != nullptr) {
				m_character->playMeleeAttackAnimation();
			//	m_characterController->playMeleeAttackAnimation();
				m_audioSource->playSFX(SFX_SWORD);
			}
			else {
				m_character->playRangeAttackAnimation();
			//	m_characterController->playRangeAttackAnimation();
				m_audioSource->playSFX(SFX_BOW);
			}
		}
	}
}

void CharacterController::useWeaponMelee()
{
	std::shared_ptr<BaseWeapon> weapon = m_inventory->getWeapon();

	if (weapon != nullptr )
	{
		if (weapon->use())
		{
			std::shared_ptr<BaseMeleeWeapon> melee = dynamic_pointer_cast<BaseMeleeWeapon>(weapon);
			if (melee != nullptr) {
				m_character->playMeleeAttackAnimation();
				//	m_characterController->playMeleeAttackAnimation();
				m_audioSource->playSFX(SFX_SWORD);
			}
		}
	}
}


bool CharacterController::tryInvokeTrigger()
{
	auto transform = getGameObject()->getTransform();
	auto closeObjects = GameManager::getInstance()->getObjectsInBounds(transform->getX(), transform->getY(), transform->getScale(), transform->getScale());

	std::shared_ptr<Invokable> closest = nullptr;
	float distance = 1000;

	for (auto it = closeObjects.begin(); it != closeObjects.end(); it++)
	{
		std::shared_ptr<Invokable> invokable = (*it)->getComponent<Invokable>();
		std::shared_ptr<BasePossessableController> possessable = nullptr;
		float maxDistance = transform->getScale() / 4.0f + (*it)->getTransform()->getScale() / 4.0f;

		if (invokable == nullptr)
		{
			possessable = (*it)->getComponent<BasePossessableController>();
			invokable = dynamic_pointer_cast<Invokable>(possessable);
			if (invokable == nullptr) 
			{
				invokable = dynamic_pointer_cast<Invokable>(*it);
			}
		}

		if (invokable != nullptr || possessable != nullptr)
		{
			float newDistance = (*it)->getTransform()->getDistance(transform);
			if (newDistance <= maxDistance && newDistance < distance)
			{
				distance = newDistance;
				closest = invokable;
			}
		}
	}

	if (closest != nullptr)
	{
		m_audioSource->playSFX(SFX_DOOR);
		closest->trigger();
		return true;
	}
	return false;
}

void CharacterController::tryNextLevel()
{
	// check if player within certain distance of staircase on this level
	int stairX = GeneratorManager::getInstance()->levels[level]->stairX;
	int stairY = GeneratorManager::getInstance()->levels[level]->stairY;
	int distance = sqrt((stairX - this->getGameObject()->getTransform()->getX()) * (stairX - this->getGameObject()->getTransform()->getX()) + (stairY - this->getGameObject()->getTransform()->getY()) * (stairY - this->getGameObject()->getTransform()->getY()));
	
	if (distance < 3 && level+1 < PYRAMID_HEIGHT)
	{
		int x = GeneratorManager::getInstance()->levels[level+1]->spawnX;
		int y = GeneratorManager::getInstance()->levels[level+1]->spawnY;
		this->getGameObject()->getTransform()->setPosition(x,y);
		level++;
	}

}


void CharacterController::useShield()
{
	std::shared_ptr<BaseWeapon> weapon = m_inventory->getWeapon();
	std::shared_ptr<BaseShield> shield = m_inventory->getShield();

	if (shield != nullptr && 
		(weapon == nullptr || !weapon->isAttacking()))
	{
		if (shield->use())
		{
			// TODO Shield SFX?
		}
	}
}

void CharacterController::useGreaves()
{
	std::shared_ptr<BaseGreaves> greaves = m_inventory->getGreaves();

	if (greaves != nullptr)
	{
		if (greaves->use())
		{
			// TODO Greaves SFX?
			m_audioSource->playSFX(SFX_DASH);
		}
	}
}

void CharacterController::takeDamage(int damage, bool isCriticalHit)
{
	std::shared_ptr<BaseShield> shield = m_inventory->getShield();
	std::shared_ptr<BaseChestplate> chestplate = m_inventory->getChestplate();
	auto realDamage = damage;

	/* Apply helmet defense. */
	if (isCriticalHit)
	{
		std::shared_ptr<BaseHelmet> helmet = m_inventory->getHelmet();

		if (helmet == nullptr || 
			!helmet->doesAvoidCriticalHit())
		{
			realDamage *= BaseWeapon::CRITICAL_HIT_DAMAGE_MULTIPLIER;
		}
	}

	/* Apply shield defense */
	if (shield != nullptr && 
		shield->isBlocking())
	{
		realDamage = shield->calculateRealDamage(realDamage);
		m_audioSource->playSFX(SFX_SHIELD);
	}

	/* Apply chestplate defense */
	if (chestplate != nullptr)
	{
		realDamage = chestplate->calculateRealDamage(realDamage);
	}

	Damageable::takeDamage(realDamage);
	std::shared_ptr<Sender> s = gameObject->getComponent<Sender> ();
	if (s != nullptr)
		s->sendHurt (Damageable::getHealth());
	m_character->playHurtAnimation();
	m_audioSource->playSFX(SFX_HIT);
	std::stringstream eventName;
	eventName << gameObject->getId() << "|HEALTHBAR";
	map<std::string, void*> eventPayload;
	auto health = std::to_string(m_health);
	auto maxHealth = std::to_string(m_maxHealth);
	eventPayload["currentHealth"] = &health;
	eventPayload["maxHealth"] = &maxHealth;
	MessageManager::sendEvent(eventName.str(), eventPayload);
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
	// If we are the player, spawn our ghost
 	bool isPlayableCharacter = dynamic_cast<PlayerPilot*>(m_pilot.get()) != nullptr;

	if (isPlayableCharacter) {
		//If we have a sender, we have a sending ID
		auto sender = gameObject->getComponent<Sender>();
		if (sender != nullptr) {
			auto newGhost = SpawnManager::getInstance()->generateNetworkGhost(gameObject->getTransform()->getX(), gameObject->getTransform()->getY(), sender->getNetworkID(), true);
			SceneManager::getInstance()->getCurrentScene()->setCameraFollow(newGhost);
		}
	}
	m_character->getTransform()->setX(-222222222);

	m_character->onEnd();
	m_character->onNetworkEnd ();
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
				std::shared_ptr<BaseItem> extractedItem = worldItem->pickupItem();
				m_audioSource->playSFX(SFX_ITEM);
				std::shared_ptr<BaseItem> removedItem = m_inventory->addItem(extractedItem);
				if (removedItem != nullptr) {
					return SpawnManager::getInstance()->generateWorldItem(worldItem->getTransform()->getX(), worldItem->getTransform()->getY(), removedItem);
				}

				break;
			}
		}
	}
	return nullptr;
}
