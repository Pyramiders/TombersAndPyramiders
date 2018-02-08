#include "Component.h"
#include "GameManager.h"

Component::Component(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

GameObject* Component::getGameObject()
{
	return gameObject;
}

Component::~Component() {}


void Component::destroy(GameObject* gameObject)
{
	GameManager::getInstance()->removeGameObject(gameObject);
}