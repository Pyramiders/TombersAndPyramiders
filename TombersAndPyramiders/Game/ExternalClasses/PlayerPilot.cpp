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
#include "Sender.h"
#include "GameManager.h"
#include "Invokable.h"
#include "BasePossessableController.h"
#include "NetworkingManager.h"

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
void PlayerPilot::setController (BaseController* controller)
{
	BasePilot::setController (controller);

	/* Store a correctly typed pointer to the controller for convenience. */
	m_characterController = static_cast<CharacterController*>(controller);
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void PlayerPilot::onStart ()
{}

void PlayerPilot::onUpdate (int ticks)
{
	if (m_characterController != nullptr)
	{
		/* Move the character. */
		m_lastMoveVector = getMovement ();
		m_characterController->move (*(m_lastMoveVector * ((float)ticks / 1000.0f)));

		/* TODO Make character face mouse position. */

		/* Use weapon. */
		if (getWeaponInput ())
		{
			m_characterController->useWeapon();
			auto sender = m_characterController->getGameObject()->getComponent<Sender>();
			if (sender != nullptr)
			{
				sender->sendAttack();
			}
		}
		else
		{
			tryInvokeTrigger ();
		}
	}
	/* Use shield. */
	if (getShieldInput ())
	{
		m_characterController->useShield ();
	}

	/* Use greaves. */
	if (getGreavesInput ())
	{
		m_characterController->useGreaves ();
	}

	/* Pick up items. */
	if (InputManager::getInstance ()->onKeyPressed (SDLK_e))
	{
		if (NetworkingManager::getInstance ()->isConnected ()) {
			if (NetworkingManager::getInstance ()->isHost ()) {
				m_characterController->trySwapItem ();
				std::shared_ptr<Sender> sender = m_characterController->getGameObject ()->getComponent<Sender> ();
				if (sender != nullptr) {
					sender->sendSwappedItem ();
				}
			}
			else {
				m_characterController->getGameObject ()->getComponent<Sender> ()->sendTrySwapItem ();
			}
		}
		else {
			m_characterController->trySwapItem ();
		}
	}
}

void PlayerPilot::tryInvokeTrigger ()
{
	if (InputManager::getInstance ()->onKeyPressed (SDLK_z))
	{
		if (m_characterController->tryInvokeTrigger()) {
			auto sender = m_characterController->getGameObject()->getComponent<Sender>();
			if (sender != nullptr)
			{
				sender->sendTrigger();
			}
		}
	}
}

void PlayerPilot::onEnd ()
{}

Vector2 PlayerPilot::getMovement ()
{
	Vector2 movement = Vector2 (0, 0);

	/* Move up. */
	if (InputManager::getInstance ()->onKey (SDLK_w))
	{
		movement.setY (movement.getY () + 1);
	}

	/* Move down. */
	if (InputManager::getInstance ()->onKey (SDLK_s))
	{
		movement.setY (movement.getY () - 1);
	}

	/* Move left. */
	if (InputManager::getInstance ()->onKey (SDLK_a))
	{
		movement.setX (movement.getX () - 1);
	}

	/* Move right. */
	if (InputManager::getInstance ()->onKey (SDLK_d))
	{
		movement.setX (movement.getX () + 1);
	}

	return movement;
}

bool PlayerPilot::getWeaponInput ()
{
	return InputManager::getInstance ()->onKeyPressed (SDLK_SPACE);
}

bool PlayerPilot::getShieldInput ()
{
	return InputManager::getInstance ()->onKeyPressed (SDLK_o);
}

bool PlayerPilot::getGreavesInput ()
{
	return InputManager::getInstance ()->onKeyPressed (SDLK_p);
}
