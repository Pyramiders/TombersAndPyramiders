/*===================================================================================*//**
	PlayerPilot
	
	A pilot that gets local keyboard input from the player.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BasePilot.h"
#include "Vector2.h"
class CharacterController;

/*========================================================================================
	PlayerPilot	
========================================================================================*/
class PlayerPilot : public BasePilot
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	private:
		//static const SDL_Keycode PLAYER_MOVE_UP_KEY;
		//static const SDL_Keycode PLAYER_MOVE_DOWN_KEY;
		//static const SDL_Keycode PLAYER_MOVE_LEFT_KEY;
		//static const SDL_Keycode PLAYER_MOVE_RIGHT_KEY;

		CharacterController* m_characterController; /* Note this is delibrately a raw pointer.
														Pilots do not own their controllers and should not delete them. */

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit PlayerPilot() = default;

		Vector2 m_lastMoveVector;
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
	public:
		/**
			This method assumes that the controller being passed is a CharacterController.
		*/
		void setController(BaseController* controller);

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		void onStart();

		/**
			Reads player input and drives the pilot's controller each frame accordingly.
		*/
		void onUpdate(int ticks);

		void onEnd();

	private:
		/**
			Determine how the character should move this frame based on player input.
		*/
		Vector2 getMovement();

		/**
			Returns whether there is input to use the character's weapon.
		*/
		bool getWeaponInput();
		
		/**
			Tries to see if there is a triggerable object within range and trigger it if so
		*/
		void tryInvokeTrigger();

		/**
			Tries to enter next level
		*/
		void tryNextLevel();

		/**
			Returns whether there is input to use the character's shield.
		*/
		bool getShieldInput();

		/**
			Returns whether there is input to use the character's greaves.
		*/
		bool getGreavesInput();
};
