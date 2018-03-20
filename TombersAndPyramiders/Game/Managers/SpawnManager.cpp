#include "SpawnManager.h"
#include <vector>
#include "GameManager.h"
#include "Inventory.h"
#include "WoodenShortsword.h"
#include "WoodenLongbow.h"
#include "PlayerPilot.h"
#include "AiPilot.h"
#include "DummyPilot.h"
#include "Receiver.h"
#include "Sender.h"
#include "NetworkingManager.h"
#include "NetworkedGameScene.h"
#include "NetworkCharacter.h"
#include "HostPilot.h"
#include "Health.h"
#include "GhostPilot.h"
#include "SingleDoor.h"
#include "WoodenShield.h"
#include "WoodenGreaves.h"
#include "WoodenChestplate.h"
#include "WoodenHelmet.h"
#include "GeneratorManager.h"

std::shared_ptr<SpawnManager> SpawnManager::s_instance;

void startGameCallback(std::map<std::string, void*> payload)
{
	std::cout << "Client Start." << std::endl;

	SpawnManager* self = (SpawnManager*)payload["this"];
	NetworkedGameScene* scene = new NetworkedGameScene();
	SceneManager::getInstance()->pushScene(scene);




	for (int i = 0; i < 4; i++)
	{
		int mapSeedID = std::stoi (*(std::string*)payload["mapSeedID" + std::to_string (i)]);
		srand (mapSeedID);
		GeneratorManager::getInstance ()->generateLevel (30, 30, 2, i);
	}
	GeneratorManager::getInstance ()->drawLevel (0);

	int players = std::stoi(*(std::string*)payload["playerSpawns"]);

	int id = 0, x = 0, y = 0;
	for (int i = 0; i < players; i++) {
		id = std::stoi(*(std::string*)payload["playerSpawnIP" + std::to_string(i)]);
		x = std::stof(*(std::string*)payload["playerSpawnX" + std::to_string(i)]);
		y = std::stof(*(std::string*)payload["playerSpawnY" + std::to_string(i)]);
		if (NetworkingManager::getInstance ()->isSelf (id))
			scene->setCameraFollow (SpawnManager::getInstance ()->generatePlayerCharacter (id, x, y));
		else
			SpawnManager::getInstance ()->generateNetworkCharacter(id, x, y);
	}

	NetworkingManager::getInstance ()->startGameClient ();
	SpawnManager::getInstance ()->stopListeningForStartPacket ();
}

void SpawnManager::sendStartPacket()
{
	std::map<std::string, std::string> payload;

	NetworkedGameScene* scene = new NetworkedGameScene();
	SceneManager::getInstance()->pushScene(scene);


	std::vector<__time64_t> mapSeeds;

	for (int i = 0; i < 4; i++)
	{
		time_t seed = time (NULL);
		srand (seed);
		GeneratorManager::getInstance ()->generateLevel (30, 30, 2, i);
		payload["mapSeedID" + std::to_string (i)] = std::to_string (seed);
	}
	GeneratorManager::getInstance ()->drawLevel (0);

	payload["playerSpawns"] = std::to_string(NetworkingManager::getInstance()->m_clients.size());

	int id = 0, x = 0, y = 0;
	payload["playerSpawnIP0"] = std::to_string(id);
	payload["playerSpawnX0"] = std::to_string(x);
	payload["playerSpawnY0"] = std::to_string(y);
	scene->setCameraFollow(SpawnManager::getInstance()->generatePlayerCharacter(id, x, y));

	int i = 1;
	for (auto it = ++NetworkingManager::getInstance()->m_clients.begin(); it != NetworkingManager::getInstance()->m_clients.end(); it++) {
		id = it->first;
		x = 2 * i;
		y = 0;
		payload["playerSpawnIP" + std::to_string(i)] = std::to_string(id);
		payload["playerSpawnX" + std::to_string(i)] = std::to_string(x);
		payload["playerSpawnY" + std::to_string(i)] = std::to_string(y);
		SpawnManager::getInstance()->generateHostCharacter(id, x, y);
		i++;
	}

	NetworkingManager::getInstance()->prepareMessageForSendingTCP(0, "STARTGAME", payload);
}

void SpawnManager::listenForStartPacket()
{
	this->m_startPacketListenerID = MessageManager::subscribe("0|STARTGAME", startGameCallback, this);
}

void SpawnManager::stopListeningForStartPacket () {
	MessageManager::unSubscribe ("0|STARTGAME", m_startPacketListenerID);
}

std::shared_ptr<SpawnManager> SpawnManager::getInstance()
{
	if (s_instance == nullptr)
		s_instance = GameManager::getInstance()->createGameObject<SpawnManager>(true);
	return s_instance;
}

SpawnManager::SpawnManager() : GameObject()
{
}

/*
This is the type of character of YOU when you are playing. It is a client character. It will only send messages out.
*/
std::shared_ptr<ClientCharacter> SpawnManager::generatePlayerCharacter(int id, float x, float y)
{
	std::shared_ptr<ClientCharacter> simpleCharacter = GameManager::getInstance()->createGameObjectWithId<ClientCharacter>(false, id, new PlayerPilot(), id);
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenLongbow>());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenShield>());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenGreaves>());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenChestplate>());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenHelmet>());
	simpleCharacter->getTransform()->setPosition(x, y, 100);

	return simpleCharacter;
}

/*
This is the type of character for everyone else IF YOU ARE HOST. They take messages and relay them back out.
*/
std::shared_ptr<HostCharacter> SpawnManager::generateHostCharacter (int id, float x, float y)
{
	std::shared_ptr<HostCharacter> simpleCharacter = GameManager::getInstance ()->createGameObjectWithId<HostCharacter> (false, id, new HostPilot (), id);
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenLongbow> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenShield> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenGreaves> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenChestplate> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenHelmet> ());
	simpleCharacter->getTransform ()->setPosition (x, y, 100);
	return simpleCharacter;
}

/*
This is the type of character for everyone else if you are NOT host. They recieve messages and send none out.
*/
std::shared_ptr<NetworkCharacter> SpawnManager::generateNetworkCharacter (int id, float x, float y)
{
	std::shared_ptr<NetworkCharacter> simpleCharacter = GameManager::getInstance ()->createGameObjectWithId<NetworkCharacter> (false, id, new HostPilot (), id);
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenLongbow> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenShield> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenGreaves> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenChestplate> ());
	simpleCharacter->getComponent<Inventory> ()->addItem (std::make_shared<WoodenHelmet> ());
	simpleCharacter->getTransform()->setPosition(x, y, 100);
	return simpleCharacter;
}

SpawnManager::~SpawnManager()
{

}

std::shared_ptr<Health> SpawnManager::generateHealth(float x, float y, string spriteName, bool hasCollider)
{
	std::shared_ptr<Health> health = GameManager::getInstance()->createGameObject<Health>(false, spriteName, hasCollider);
	health->getTransform()->setPosition(x, y);
	health->getTransform()->setScale(10);
	return health;
}

std::shared_ptr<MiscSquare> SpawnManager::generateMiscSquare(float x, float y, float z, float scale, string spriteName, bool hasCollider, float colliderSize_x, float colliderSize_y)
{
	std::shared_ptr<MiscSquare> miscSquare = GameManager::getInstance()->createGameObject<MiscSquare>(false, spriteName, hasCollider, colliderSize_x, colliderSize_y);
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
	simpleAi->getComponent<Inventory>()->addItem(std::make_shared<WoodenChestplate>());
	simpleAi->getComponent<Inventory>()->addItem(std::make_shared<WoodenHelmet>());
	simpleAi->getTransform()->setPosition(x, y);

	return simpleAi;
}

std::shared_ptr<Character> SpawnManager::generateDummyCharacter(float x, float y)
{
	std::shared_ptr<Character> simpleCharacter = GameManager::getInstance()->createGameObject<Character>(false, new DummyPilot());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenShortsword>());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenChestplate>());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<WoodenHelmet>());
	simpleCharacter->getTransform()->setPosition(x, y);

	return simpleCharacter;
}

std::shared_ptr<WorldItem> SpawnManager::generateWorldItem(float x, float y, std::shared_ptr<BaseItem> item) 
{
	std::shared_ptr<WorldItem> worldItem = GameManager::getInstance()->createGameObject<WorldItem>(false, item, x, y);
	worldItem->addComponent<BoxCollider>(worldItem.get(), 1, 1)->setIsTrigger(true);
	return worldItem;
}


std::shared_ptr<Boulder> SpawnManager::generateBoulder(float x, float y)
{
	std::shared_ptr<Boulder> boulder = GameManager::getInstance()->createGameObject<Boulder>(false, nullptr);
	boulder->getTransform()->setPosition(x, y);
	return boulder;
}


std::shared_ptr<GhostCharacter> SpawnManager::generateGhost(float x, float y)
{
	std::shared_ptr<GhostCharacter> ghost = GameManager::getInstance()->createGameObject<GhostCharacter>(false, new GhostPilot());
	ghost->getTransform()->setPosition(x, y);
	ghost->getTransform()->setZ(2);
	return ghost;
}

std::shared_ptr<SingleDoor> SpawnManager::generateSingleDoor(float x, float y, Door::Direction direction, Door::Mode startState)
{
	auto scale = 3.0f;
	std::shared_ptr<SingleDoor> door = GameManager::getInstance()->createGameObject<SingleDoor>(false, direction, startState, x, y, scale);
	door->getTransform()->setZ(1000);
	door->getTransform()->setScale(10.0f);
	if (direction == Door::Direction::West || direction == Door::Direction::East)
	{
		door->getTransform()->addRotation(180);
	}
	return door;
}

//std::shared_ptr<Wall> SpawnManager::generateWall(float x, float y, float scale)
//{
//	std::shared_ptr<Wall> wall = GameManager::getInstance()->createGameObject<Wall>(false);
//	wall->getTransform()->setPosition(x, y);
//	wall->getTransform()->setScale(scale);
//
//	return wall;
//}