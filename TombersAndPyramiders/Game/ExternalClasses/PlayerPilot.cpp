/*===================================================================================*//**
	PlayerPilot
	
	A pilot that gets local keyboard input from the player.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "PlayerPilot.h"
#include "CharacterController.h"
#include "InputManager.h"
#include "Vector2.h"

/*----------------------------------------------------------------------------------------
	Instance Setter Methods
----------------------------------------------------------------------------------------*/
//const SDL_Keycode PlayerPilot::PLAYER_MOVE_UP_KEY = SDLK_w;
//const SDL_Keycode PlayerPilot::PLAYER_MOVE_DOWN_KEY = SDLK_s;
//const SDL_Keycode PlayerPilot::PLAYER_MOVE_LEFT_KEY = SDLK_a;
//const SDL_Keycode PlayerPilot::PLAYER_MOVE_RIGHT_KEY = SDLK_d;

/*----------------------------------------------------------------------------------------
	Instance Setter Methods
----------------------------------------------------------------------------------------*/
void PlayerPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);

	/* Store a correctly typed pointer to the controller for convenience. */
	m_characterController = static_cast<CharacterController*>(controller);
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void PlayerPilot::onStart()
{}

void PlayerPilot::onUpdate(int ticks)
{
	if (m_characterController != nullptr)
	{
		m_characterController->move(getMovement());
	}
}

void PlayerPilot::onEnd()
{}

Vector2 PlayerPilot::getMovement()
{
	Vector2 movement = Vector2(0, 0);

	/* Move up. */
	if (InputManager::getInstance()->onKey(SDLK_w))
	{
		movement.setY(movement.getY() + 1);
	}

	/* Move down. */
	if (InputManager::getInstance()->onKey(SDLK_s))
	{
		movement.setY(movement.getY() - 1);
	}

	/* Move left. */
	if (InputManager::getInstance()->onKey(SDLK_a))
	{
		movement.setX(movement.getX() - 1);
	}

	/* Move right. */
	if (InputManager::getInstance()->onKey(SDLK_d))
	{
		movement.setX(movement.getX() + 1);
	}

	return movement;
}