#include "SpawnManager.h"
#include <vector>
#include "GameManager.h"
#include "Inventory.h"
#include "WoodenShortsword.h"
#include "WoodenLongbow.h"
#include "PlayerPilot.h"
#include "AiPilot.h"
#include "DummyPilot.h"

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

std::shared_ptr<MiscSquare> SpawnManager::generateMiscSquare(float x, float y, float z, float scale, string spriteName, bool hasCollider)
{
	std::shared_ptr<MiscSquare> miscSquare = GameManager::getInstance()->createGameObject<MiscSquare>(false, spriteName, hasCollider);
	miscSquare->getTransform()->setPosition(x, y, z);
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
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenShortsword>());
	simpleCharacter->getTransform()->setPosition(x, y);
	
	return simpleCharacter;
}

std::shared_ptr<Character> SpawnManager::generateAiCharacter(float x, float y)
{
	std::shared_ptr<Character> simpleAi = GameManager::getInstance()->createGameObject<Character>(false, new AiPilot());
	simpleAi->getComponent<Inventory>()->addItem(std::make_shared<WoodenLongbow>());
	simpleAi->getTransform()->setPosition(x, y);

	return simpleAi;
}
/*std::shared_ptr<Character> SpawnManager::generateAiCharacter1(float x, float y)
{
	std::shared_ptr<Character> simpleAi = GameManager::getInstance()->createGameObject<Character>(false, new AiPilot());
	simpleAi->getComponent<Inventory>()->addItem(std::make_shared<WoodenLongbow>());
	simpleAi->getTransform()->setPosition(x, y);

	return simpleAi;
}*/



std::shared_ptr<Character> SpawnManager::generateDummyCharacter(float x, float y)
{
	std::shared_ptr<Character> simpleCharacter = GameManager::getInstance()->createGameObject<Character>(false, new DummyPilot());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenShortsword>());
	simpleCharacter->getTransform()->setPosition(x, y);

	return simpleCharacter;
}

std::shared_ptr<WorldItem> SpawnManager::generateWorldItem(float x, float y, std::shared_ptr<BaseItem> item) 
{
	std::shared_ptr<WorldItem> worldItem = GameManager::getInstance()->createGameObject<WorldItem>(false, item, x, y);
	worldItem->addComponent<BoxCollider>(worldItem.get(), 1, 1)->setIsTrigger(true);
	return worldItem;
}

//std::shared_ptr<Wall> SpawnManager::generateWall(float x, float y, float scale)
//{
//	std::shared_ptr<Wall> wall = GameManager::getInstance()->createGameObject<Wall>(false);
//	wall->getTransform()->setPosition(x, y);
//	wall->getTransform()->setScale(scale);
//
//	return wall;
//}