/*===================================================================================*//**
	CharacterController
	
	A controller that controls a player character.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseController.h"
#include "Damageable.h"
#include "Vector2.h"
#include "PlayerPilot.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "BasePilot.h"
#include "WorldItem.h"
#include "Rigidbody.h"
#include "Audio\AudioSource.h"
#include "Audio\AudioListener.h"

class Inventory;

/*========================================================================================
	CharacterController	
========================================================================================*/
class CharacterController : public BaseController, public Damageable
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	public:
		static const int DEFAULT_CHARACTER_MAX_HP;
		static const Vector2 DEFAULT_CHARACTER_MOVEMENT_SPEED;

	private:
		Inventory* m_inventory;
		Vector2 m_movementSpeed;
		std::shared_ptr<Rigidbody> m_rigidbody;
		std::shared_ptr<BoxCollider> m_boxCollider;
		std::shared_ptr<AudioSource> m_audioSource;
		std::shared_ptr<AudioListener> m_audioListener;
		std::shared_ptr<Character> m_character;
    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        explicit CharacterController() = delete;

		explicit CharacterController(GameObject* parentGameobject, Inventory* inventory, BasePilot*
			pilot = nullptr, int maxHealth = DEFAULT_CHARACTER_MAX_HP, 
			Vector2 movementSpeed = DEFAULT_CHARACTER_MOVEMENT_SPEED);

    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
	public:
		/**
			Forwards the onUpdate() call to the pilot.
		*/
		void onUpdate(int ticks);
		void onStart();

		/**
			Moves this component's gameObject.

			The Vector2 passed in should have values of 1, -1, or 0 for its x and y, to 
			indicate positive, negative, or no movement along the x and y axes.

			The CharacterController will handle determining the speed of movement.
		*/
		void move(Vector2 moveInput);

		/**
			Uses the character's weapon this frame.
		*/
		void useWeapon();

		/**
			Tries to trigger around the player the closest available thing, returning true if something triggered
		*/
		bool tryInvokeTrigger();

		/*
			Uses the character's shield this frame.
		*/
		void useShield();

		/**
			Use the character's greaves this frame.
		*/
		void useGreaves();

		/**
			Picks up the given WorldItem, extracting its BaseItem and equiping it. Returns the item we put down that was previously equipped, or nullptr if none were equipped prior.
			If no item to pickup, it also returns nullptr, as its a failure to swap
		*/
		std::shared_ptr<WorldItem> trySwapItem();

		/**
			Applies the given amount of damage to the character.
			Applies double damage if isCriticalHit, unless an equipped item nullifies the critical damage.
			
			The character will handle applying any scaling of this value 
			based on buffs and equipment.
		*/
		virtual void takeDamage(int damage, bool isCriticalHit);

	protected:
		/**
			Called when the character's HP reaches zero.
			Handles the player's death.
		*/
		void death();
	
	private:
		/**
			Forwards the onUpdate() call to the character's weapon.
		*/
		void updateWeapon(int ticks);

		/**
			Forwards the onUpdate() call to the character's shield.
		*/
		void updateShield(int ticks);

		/**
			Forwards the onUpdate() call to the character's greaves.
		*/
		void updateGreaves(int ticks);
};
