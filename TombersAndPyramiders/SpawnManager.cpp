#include "SpawnManager.h"
#include <vector>

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
	std::shared_ptr<MiscSquare> miscSquare = std::shared_ptr<MiscSquare>(new MiscSquare());
	miscSquare->getTransform()->setPosition(x, y);
	miscSquare->getTransform()->setScale(scale);
	miscSquares.push_back(miscSquare);
	return miscSquare;
}

std	::shared_ptr<MovingSquare> SpawnManager::generateMovingSquare(float x, float y)
{
	std::shared_ptr<MovingSquare> movingSquare = std::shared_ptr<MovingSquare>(new MovingSquare());
	movingSquare->getTransform()->setPosition(x, y);
	movingSquares.push_back(movingSquare);
	return movingSquare;
}

std::shared_ptr<PlayerCharacter> SpawnManager::generateSimpleCharacter(float x, float y)
{
	std::shared_ptr<PlayerCharacter> simpleCharacter = std::shared_ptr<PlayerCharacter>(new PlayerCharacter());
	simpleCharacter->getTransform()->setPosition(x, y);
	simpleCharacters.push_back(simpleCharacter);
	return simpleCharacter;
}