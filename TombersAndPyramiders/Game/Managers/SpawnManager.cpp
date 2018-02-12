#include "SpawnManager.h"
#include <vector>
#include "GameManager.h"
#include "Inventory.h"
#include "WoodenShortsword.h"
#include "WoodenLongbow.h"
#include "PlayerPilot.h"

SpawnManager* SpawnManager::s_instance;

SpawnManager* SpawnManager::getInstance()
{
	if (s_instance == nullptr)
		s_instance = new SpawnManager();
	return s_instance;
}

SpawnManager::SpawnManager()
{

}

SpawnManager::~SpawnManager()
{

}

std::shared_ptr<MiscSquare> SpawnManager::generateMiscSquare(float x, float y, float scale)
{
	std::shared_ptr<MiscSquare> miscSquare = GameManager::getInstance()->createGameObject<MiscSquare>(false);
	miscSquare->getTransform()->setPosition(x, y);
	miscSquare->getTransform()->setScale(scale);
	return miscSquare;
}

std	::shared_ptr<MovingSquare> SpawnManager::generateMovingSquare(float x, float y)
{
	std::shared_ptr<MovingSquare> movingSquare = GameManager::getInstance()->createGameObject<MovingSquare>(false);
	movingSquare->getTransform()->setPosition(x, y);
	return movingSquare;
}

std::shared_ptr<Character> SpawnManager::generatePlayerCharacter(float x, float y)
{
	std::shared_ptr<Character> simpleCharacter = GameManager::getInstance()->createGameObject<Character>(false, new PlayerPilot());
	simpleCharacter->getComponent<Inventory>()->addItem(new WoodenLongbow());
	simpleCharacter->getTransform()->setPosition(x, y);
	
	return simpleCharacter;
}

