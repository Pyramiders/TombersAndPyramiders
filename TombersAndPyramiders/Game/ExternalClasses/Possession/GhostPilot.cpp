#include "GhostPilot.h"
#include "InputManager.h"
#include "Vector2.h"
#include "GameManager.h"
#include "BasePossessableController.h"
#include "GhostController.h"

GhostPilot::GhostPilot() {
	m_ghostController = nullptr;
}

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
	//If we are possessing something
	if (m_possessableController != nullptr)
	{
		//Possessing + Space = Trigger
		if (InputManager::getInstance()->onKeyPressed(SDLK_SPACE))
		{
			m_possessableController->trigger();
		}
		//Possessing + E = Stop Possessing
		else if (InputManager::getInstance()->onKeyPressed(SDLK_q))
		{
			std::cout << "UNPOSSESSING!" << std::endl;
			m_possessableController->swapPilots(m_ghostController);
			m_possessableController->onPossessionEnd();
			m_possessableController = nullptr;
			m_ghostController->getGameObject()->getTransform()->setScale(1.0f);
		}
	}
	//If we are not possessing anything
	else
	{
		if (m_ghostController != nullptr) //Regular controller for moving the Ghost
		{
			//Not Possessing + Movement = Move Ghost
			GhostController* controller = dynamic_cast<GhostController*>(m_controller);
			if (controller != nullptr)
			{
				controller->move(getMovement());
				//Not Possessing + E = Try To Possess
				if (InputManager::getInstance()->onKeyPressed(SDLK_e))
				{
					Transform* transform = m_controller->getGameObject()->getTransform();
					std::vector<std::shared_ptr<GameObject>> gameObjects = GameManager::getInstance()->getObjectsInBounds(transform->getX(), transform->getY(), 2.0f, 2.0f);
					for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
					{
						std::shared_ptr<BasePossessableController> possessionController = (*it)->getComponent<BasePossessableController>();
						if (possessionController != nullptr) //If we pressed E on something we can possess
						{
							std::cout << "POSSESSINGG!" << std::endl;
							m_ghostController->getGameObject()->getTransform()->setScale(0.0f);
							m_controller->swapPilots(possessionController.get());
							m_possessableController = possessionController;
							m_possessableController->onPossessionStart();
							break;
						}
					}

				}
			}
			else 
			{
				std::cout << "ERROR::GHOSTPILOT::ONUPDATE::No GhostController or BasePossessableController attacked" << std::endl;
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
