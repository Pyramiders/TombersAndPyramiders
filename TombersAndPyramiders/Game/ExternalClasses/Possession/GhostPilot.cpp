#include "GhostPilot.h"
#include "InputManager.h"
#include "Vector2.h"
#include "GameManager.h"
#include "GhostController.h"
#include "BasePossessableController.h"

GhostPilot::GhostPilot() {
	m_ghostController = nullptr;
	m_justSwapped = false;
}

//On loading in a controller, if it's our first time loading the m_ghostController, set it
void GhostPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);
	if (m_ghostController == nullptr)
	{
		m_possessableController = nullptr;
		m_ghostController = m_controller;
	}
}

void GhostPilot::onUpdate(int ticks)
{
	//If we swapped and no longer are in a swappable state, reset the flag
	if (m_justSwapped && InputManager::getInstance()->onKeyReleased(SDLK_e))
	{
		m_justSwapped = false;
	}

	//If we are possessing something
	if (m_possessableController != nullptr)
	{
		//Possessing + Space = Attack with the possessable controller
		if (InputManager::getInstance()->onKeyPressed(SDLK_SPACE))
		{
			m_possessableController->trigger();
		}
		//Possessing + E = Stop Possessing
		else if (checkShouldSwap())
		{
			Transform* possessTrans = m_possessableController->getGameObject()->getTransform();
			m_ghostController->getGameObject()->getTransform()->setPosition(possessTrans->getX(), possessTrans->getY());
			m_possessableController->swapPilots(m_ghostController);
			m_possessableController->onPossessionEnd();
			m_possessableController = nullptr;
			m_ghostController->getGameObject()->getTransform()->setScale(1.0f);
			m_justSwapped = true;
			GhostController* ghostControllerRaw = dynamic_cast<GhostController*>(m_controller);
			if (ghostControllerRaw != nullptr)
			{
				ghostControllerRaw->stopPossessing();
			}
		}
		//Possessing + Anything else = Movement, which will be (0,0) if not moving
		else
		{
			Vector2 movement = getMovement();
			m_possessableController->move(movement);
		}
	}
	//If we are not possessing anything
	else
	{
		//Regular controller for moving the Ghost
		if (m_ghostController != nullptr)
		{
			//Not Possessing + Movement = Move Ghost
			GhostController* ghostControllerRaw = dynamic_cast<GhostController*>(m_controller);
			if (ghostControllerRaw != nullptr)
			{
				ghostControllerRaw->move(getMovement());
				//Not Possessing + E = Try To Possess
				if (checkShouldSwap())
				{
					Transform* transform = m_controller->getGameObject()->getTransform();
					std::vector<std::shared_ptr<GameObject>> gameObjects = GameManager::getInstance()->getObjectsInBounds(transform->getX(), transform->getY(), 3.0f, 3.0f); //Get all objects within 2x2 of our Ghost
					std::shared_ptr<BasePossessableController> closest = nullptr;
					float distance = 1000;
					
					for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
					{
						std::shared_ptr<BasePossessableController> possessionController = (*it)->getComponent<BasePossessableController>();
						if (possessionController != nullptr)
						{
							float newDistance = (*it)->getTransform()->getDistance(transform);
							if (newDistance < distance)
							{
								distance = newDistance;
								closest = possessionController;
							}
						}
					}

					if (closest != nullptr && ghostControllerRaw->tryPossess(closest)) //Try and possess, make sure its close enough
					{
						m_controller->swapPilots(closest.get());
						m_possessableController = closest;
						m_possessableController->onPossessionStart();
						m_justSwapped = true;
					}
				}
			}
			else 
			{
				std::cout << "ERROR::GHOSTPILOT::ONUPDATE::No GhostController or BasePossessableController attached" << std::endl;
			}
		}
		else {
			std::cout << "ERROR::GHOSTPILOT::ONUPDATE::Not possessing anything and no controller" << std::endl;
		}
	}
}

void GhostPilot::onStart()
{}

void GhostPilot::onEnd()
{}

bool GhostPilot::checkShouldSwap()
{
	return !m_justSwapped && InputManager::getInstance()->onKeyPressed(SDLK_e);
}

Vector2 GhostPilot::getMovement()
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

