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
		static const int DEFAULT_PLAYER_MAX_HP;
		static const Vector2 DEFAULT_PLAYER_MOVEMENT_SPEED;

	private:
		Inventory* m_inventory;
		Vector2 m_movementSpeed;

		std::shared_ptr<PlayerCharacter> m_playerCharacter;
    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        explicit CharacterController() = delete;

		explicit CharacterController(GameObject* parentGameobject, Inventory* inventory, BasePilot*
			pilot = new PlayerPilot(), int maxHealth = DEFAULT_PLAYER_MAX_HP, 
			Vector2 movementSpeed = DEFAULT_PLAYER_MOVEMENT_SPEED);

    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
	public:
		/**
			Forwards the onUpdate() call to the pilot.
		*/
		void onUpdate(int ticks);

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

	protected:
		/**
			Called when the character's HP reaches zero.
			Handles the player's death.
		*/
		void death();
};
