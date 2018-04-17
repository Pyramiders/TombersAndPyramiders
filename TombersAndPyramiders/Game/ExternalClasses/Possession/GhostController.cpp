#include "GhostController.h"
#include "BasePossessableController.h"
#include "GhostCharacter.h"
#include "GameManager.h"

const float GhostController::MAX_POSSESSION_DISTANCE = 3.0f;
Vector2 GhostController::DEFAULT_MOVE_SPEED = Vector2(0.2f, 0.2f);

GhostController::GhostController(GameObject* parentGameobject, BasePilot* pilot) : BaseController(parentGameobject, pilot)
{
	m_toFollow = nullptr;
}

void GhostController::onStart()
{
	std::cout << "GhostController::OnStart" << std::endl;
}

//Update the pilot, and if we're following someone, follow them
void GhostController::onUpdate(int ticks)
{
	if (m_pilot != nullptr)
	{
		m_pilot->onUpdate(ticks);
	}
	if (m_toFollow != nullptr)
	{
		gameObject->getTransform()->setPosition(m_toFollow->getGameObject()->getTransform()->getX(), m_toFollow->getGameObject()->getTransform()->getY());
	}
}

bool GhostController::tryPossessClosest(std::shared_ptr<BasePossessableController>& toCheck) {
	Transform* transform = getGameObject()->getTransform();
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

	if (closest != nullptr) {
		toCheck = closest;
		return tryPossess(closest);
	}
	return false;
}

//Try to possess an object. If they are close enough to possess, possess them and follow the object
bool GhostController::tryPossess(std::shared_ptr<BasePossessableController> toPossess)
{
	if (toPossess != nullptr)
	{
		if (gameObject->getTransform()->getDistance(toPossess->getGameObject()->getTransform()) <= MAX_POSSESSION_DISTANCE)
		{
			GhostCharacter* ghost = dynamic_cast<GhostCharacter*>(gameObject);
			if (ghost != nullptr)
			{
				follow(toPossess);
				ghost->setMode(GhostCharacter::Mode::possessing);
				return true;
			}
		}
	}
	return false;
}

//Stop possessing objects and stop following them
void GhostController::stopPossessing()
{
	follow(nullptr);
	GhostCharacter* ghost = dynamic_cast<GhostCharacter*>(gameObject);
	if (ghost != nullptr)
	{
		ghost->setMode(GhostCharacter::Mode::ghost);
	}
}

//Follow an object
void GhostController::follow(std::shared_ptr<BasePossessableController>  toFollow)
{
	m_toFollow = toFollow;
}

std::shared_ptr<BasePossessableController> GhostController::getPossessingItem()
{
	return m_toFollow;
}

//Take in a delta vector, turn it into a direcitonal movespeed vector and determine which direction to move
void GhostController::move(Vector2 delta)
{
	delta.setX(delta.getX() * DEFAULT_MOVE_SPEED.getX());
	delta.setY(delta.getY() * DEFAULT_MOVE_SPEED.getY());

	if (delta.getMagnitude() == 0)
	{
	}
	else
	{
		gameObject->getTransform()->setRotation(delta.getRotationInDegrees());
	}

	gameObject->getTransform()->addTranslation(delta.getX(), delta.getY());
}
