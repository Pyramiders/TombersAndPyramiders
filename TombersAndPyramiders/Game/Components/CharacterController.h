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
		Vector2 m_movementSpeed;

		bool m_wasUsingWeapon;
		bool m_wasUsingShield;
		bool m_wasUsingGreaves;

		bool m_isUsingWeapon;
		bool m_isUsingShield;
		bool m_isUsingGreaves;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        explicit CharacterController() = delete;

		explicit CharacterController(GameObject* gameObject, BasePilot* pilot = new PlayerPilot(), 
			int maxHealth = DEFAULT_PLAYER_MAX_HP, Vector2 movementSpeed = DEFAULT_PLAYER_MOVEMENT_SPEED);

	
    /*----------------------------------------------------------------------------------------
		Instance Setter Methods
    ----------------------------------------------------------------------------------------*/
	public:
		void setIsUsingWeapon(bool isUsingWeapon);
		void setIsUsingShield(bool isUsingShield);
		void setIsUsingGreaves(bool isUsingGreaves);

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
	
	private:
		/**
			Updates the player's weapon this tick.

			This will either start, continue, or stop the use of the weapon, 
			depending on what input was received in the past two frames.
		*/
		void updateWeapon(int ticks);

		/**
			Updates the player's shield this tick.

			This will either start, continue, or stop the use of the shield, 
			depending on what input was received in the past two frames.
		*/
		void updateShield(int ticks);

		/**
			Updates the player's greaves this tick.

			This will either start, continue, or stop the use of the greaves, 
			depending on what input was received in the past two frames.
		*/
		void updateGreaves(int ticks);

	protected:
		/**
			Called when the character's HP reaches zero.
			Handles the player's death.
		*/
		void death();
};
