#include "SpawnManager.h"
#include <vector>
#include "GameManager.h"
#include "Inventory.h"
#include "PlayerPilot.h"
#include "AiPilot.h"
#include "DummyPilot.h"
#include "Receiver.h"
#include "Sender.h"
#include "NetworkingManager.h"
#include "NetworkedGameScene.h"
#include "NetworkCharacter.h"
#include "HostPilot.h"
#include "GhostPilot.h"
#include "SingleDoor.h"
#include "GeneratorManager.h"
#include "GhostReceiverPilot.h"
#include "OldTestScene.h"
#include "EquipmentIncludes.h"
#include "Camera.h"
#include "FogOfWarCamera.h"
#include "Light.h"
#include "GhostCamera.h"
#include "Randomize.h"
#include "HealthBar.h"
#include "Throne.h"
#include "AudioManager.h"

std::shared_ptr<SpawnManager> SpawnManager::s_instance;

void startGameCallback(std::map<std::string, void*> payload)
{
	std::cout << "Client Start." << std::endl;

	SpawnManager* self = (SpawnManager*)payload["this"];
	NetworkedGameScene* scene = new NetworkedGameScene();
	SceneManager::getInstance()->pushScene(scene);

	for (int i = 0; i < PYRAMID_HEIGHT; i++)
	{
		int mapSeedID = std::stoi (*(std::string*)payload["mapSeedID" + std::to_string (0)]);
		Randomize::SetSeed(mapSeedID);
		GeneratorManager::getInstance ()->generateLevel (WORLD_WIDTH, WORLD_HEIGHT, 2, i);
		GeneratorManager::getInstance()->drawLevel(i);
		GeneratorManager::getInstance()->reset();
	}


	int players = std::stoi(*(std::string*)payload["playerSpawns"]);

	int id = 0, x = 0, y = 0;
	for (int i = 0; i < players; i++) {
		id = std::stoi(*(std::string*)payload["playerSpawnIP" + std::to_string(i)]);
		x = std::stof(*(std::string*)payload["playerSpawnX" + std::to_string(i)]);
		y = std::stof(*(std::string*)payload["playerSpawnY" + std::to_string(i)]);
		if (NetworkingManager::getInstance()->isSelf(id))
		{
			std::shared_ptr<Character> generatedCharacter = SpawnManager::getInstance()->generatePlayerCharacter(id, x, y);
			scene->setCameraFollow(generatedCharacter);
			SpawnManager::getInstance()->allPlayers.push_back(generatedCharacter);
		
		}
		else
		{
			SpawnManager::getInstance()->allPlayers.push_back(SpawnManager::getInstance()->generateNetworkCharacter(id, x, y));
		}
	}

	for (int i = 0; i < 5 * PYRAMID_HEIGHT; i++) {
		id = std::stoi (*(std::string*)payload["aiSpawnID" + std::to_string (i)]);
		x = std::stoi (*(std::string*)payload["aiSpawnX" + std::to_string (i)]);
		y = std::stoi (*(std::string*)payload["aiSpawnY" + std::to_string (i)]);
		SpawnManager::getInstance ()->generateAiCharacter (id, x, y, false);

	//	SpawnManager::getInstance()->generateBossAiCharacter(id, x, y, false);
		
	}

	NetworkingManager::getInstance ()->startGameClient ();
	SpawnManager::getInstance ()->stopListeningForStartPacket ();
}

void SpawnManager::sendStartPacket()
{
	//---------------------------------------------------------- TODO-ERICK Comment out these lines before pushing.
	//OldTestScene* testScene = new OldTestScene();
	//SceneManager::getInstance()->pushScene(testScene);
	//return;
	//----------------------------------------------------------

	std::map<std::string, std::string> payload;

	NetworkedGameScene* scene = new NetworkedGameScene();
	SceneManager::getInstance()->pushScene(scene);	
	

	std::vector<time_t> mapSeeds;	

	int id = 30000, x = 0, y = 0;
	for (int i = 0; i < PYRAMID_HEIGHT; i++)
	{
		time_t seed = time(NULL);
		Randomize::SetSeed(seed);
		GeneratorManager::getInstance()->generateLevel(WORLD_WIDTH, WORLD_HEIGHT, 2, i);
		payload["mapSeedID" + std::to_string(i)] = std::to_string(seed);
		GeneratorManager::getInstance()->drawLevel(i);

		//ai spawns
		int room = Randomize::Random(0, GeneratorManager::getInstance()->levels[i]->rooms.size() - 2);

		for (int j = 0; j < 5; j++) {
			x = ((Randomize::Random() % (GeneratorManager::getInstance()->levels[i]->rooms[room]->m_width - 2) + 1) + GeneratorManager::getInstance()->levels[i]->rooms[room]->m_xCoord) * 5;
			y = (GeneratorManager::getInstance()->levels[i]->rooms[room]->m_yCoord - (Randomize::Random() % (GeneratorManager::getInstance()->levels[i]->rooms[room]->m_height - 2) + 1)) * 5;
			x += i * LEVEL_OFFSET;
			SpawnManager::getInstance ()->generateAiCharacter (id, x, y, true);

			payload["aiSpawnID" + std::to_string (j + (5 * i))] = std::to_string (id++);
			payload["aiSpawnX" + std::to_string (j + (5 * i))] = std::to_string (x);
			payload["aiSpawnY" + std::to_string (j + (5 * i))] = std::to_string (y);
			std::cout << payload["aiSpawnID" + std::to_string(j + (5 * i))] << " " << payload["aiSpawnX" + std::to_string(j + (5 * i))] << " " << payload["aiSpawnY" + std::to_string(j + (5 * i))] << std::endl;
			//SpawnManager::getInstance()->generateBossAiCharacter(id, x, y, false);

		}

		for (int r = 0; r < GeneratorManager::getInstance()->levels[i]->rooms.size(); r++) {
			for (int am = 0; am < 6; am++) {
				x = ((Randomize::Random() % (GeneratorManager::getInstance()->levels[i]->rooms[r]->m_width - 3) + 1) + GeneratorManager::getInstance()->levels[i]->rooms[r]->m_xCoord) * 5;
				y = (GeneratorManager::getInstance()->levels[i]->rooms[r]->m_yCoord - (Randomize::Random() % (GeneratorManager::getInstance()->levels[i]->rooms[r]->m_height - 3) + 1)) * 5;
				SpawnManager::getInstance()->generateSpikes(x + Randomize::Random(0, 4), y + Randomize::Random(0, 4));
				if (am > 3) {
					SpawnManager::getInstance()->generateDartTrap(x + (Randomize::Random(0, 4) - 2), y + (Randomize::Random(0, 4) - 2), (DartTrap::Direction)Randomize::Random(0, 3));
				}
			}
		}
	}


	payload["playerSpawns"] = std::to_string(NetworkingManager::getInstance()->m_clients.size());

	int room = Randomize::Random(0, GeneratorManager::getInstance()->levels[0]->rooms.size() - 2);
	x = ((Randomize::Random() % (GeneratorManager::getInstance()->levels[0]->rooms[room]->m_width - 2) + 1) + GeneratorManager::getInstance()->levels[0]->rooms[room]->m_xCoord) * 5;
	y = (GeneratorManager::getInstance()->levels[0]->rooms[room]->m_yCoord - (Randomize::Random(0, GeneratorManager::getInstance()->levels[0]->rooms[room]->m_height - 3) + 1)) * 5;

	payload["playerSpawnIP0"] = std::to_string(id);
	payload["playerSpawnX0"] = std::to_string(x);
	payload["playerSpawnY0"] = std::to_string(y);

	std::shared_ptr<Character> generatedCharacter = SpawnManager::getInstance()->generatePlayerCharacter(id, x, y);
	scene->setCameraFollow(generatedCharacter);
	SpawnManager::getInstance()->allPlayers.push_back(generatedCharacter);

	int i = 1;
	for (auto it = ++NetworkingManager::getInstance()->m_clients.begin(); it != NetworkingManager::getInstance()->m_clients.end(); it++) {
		id = it->first;
		x = ((Randomize::Random(0, GeneratorManager::getInstance()->levels[0]->rooms[room]->m_width - 3) + 1) + GeneratorManager::getInstance()->levels[0]->rooms[room]->m_xCoord)*5;
		y = (GeneratorManager::getInstance()->levels[0]->rooms[room]->m_yCoord - (Randomize::Random(0, GeneratorManager::getInstance()->levels[0]->rooms[room]->m_height - 3) + 1))*5;

		payload["playerSpawnIP" + std::to_string(i)] = std::to_string(id);
		payload["playerSpawnX" + std::to_string(i)] = std::to_string(x);
		payload["playerSpawnY" + std::to_string(i)] = std::to_string(y);
		allPlayers.push_back(SpawnManager::getInstance()->generateHostCharacter(id, x, y));
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
This is the type of character of YOU are when you are playing. It is a client character. It will only send messages out.
*/
std::shared_ptr<ClientCharacter> SpawnManager::generatePlayerCharacter(int id, float x, float y)
{
	std::shared_ptr<ClientCharacter> simpleCharacter = GameManager::getInstance()->createGameObjectWithId<ClientCharacter>(false, id, new PlayerPilot(), id);

	auto healthBar = GameManager::getInstance()->createGameObject<HealthBar>(false);
	healthBar->setTrackingPlayer(simpleCharacter);
	simpleCharacter->addComponent<Light>(simpleCharacter.get())->setColor(255, 50, 50)->setSize(24.0f);
	simpleCharacter->getTransform()->setPosition(x, y, 100);
	simpleCharacter->getTransform()->setScale(2);
	simpleCharacter->getTransform()->renderRotation = false;
	m_clientPlayer = simpleCharacter;
	return simpleCharacter;
}

/*
This is the type of character for everyone else IF YOU ARE HOST. They take messages and relay them back out.
*/
std::shared_ptr<HostCharacter> SpawnManager::generateHostCharacter (int id, float x, float y)
{
	std::shared_ptr<HostCharacter> simpleCharacter = GameManager::getInstance ()->createGameObjectWithId<HostCharacter> (false, id, new HostPilot (), id);
	auto healthBar = GameManager::getInstance()->createGameObject<HealthBar>(false);
	healthBar->setTrackingPlayer(simpleCharacter);
	simpleCharacter->addComponent<Light>(simpleCharacter.get())->setColor(255, 50, 50)->setSize(14.0f);
	simpleCharacter->getTransform ()->setPosition (x, y, 100);
	simpleCharacter->getTransform()->setScale(2);
	simpleCharacter->getTransform()->renderRotation = false;
	return simpleCharacter;
}

/*
This is the type of character for everyone else if you are NOT host. They recieve messages and send none out.
*/
std::shared_ptr<NetworkCharacter> SpawnManager::generateNetworkCharacter (int id, float x, float y)
{
	std::shared_ptr<NetworkCharacter> simpleCharacter = GameManager::getInstance ()->createGameObjectWithId<NetworkCharacter> (false, id, new HostPilot (), id);
	auto healthBar = GameManager::getInstance()->createGameObject<HealthBar>(false);
	healthBar->setTrackingPlayer(simpleCharacter);
	simpleCharacter->addComponent<Light>(simpleCharacter.get())->setColor(255, 50, 50)->setSize(14.0f);
	simpleCharacter->getTransform()->setPosition(x, y, 100);
	simpleCharacter->getTransform()->setScale(2);
	simpleCharacter->getTransform()->renderRotation = false;

	return simpleCharacter;
}

SpawnManager::~SpawnManager()
{

}

std::shared_ptr<MiscSquare> SpawnManager::generateMiscSquare(float x, float y, float z, float scale, string spriteName, bool hasCollider, float colliderSize_x, float colliderSize_y)
{
	std::shared_ptr<MiscSquare> miscSquare = GameManager::getInstance()->createGameObject<MiscSquare>(false, spriteName, hasCollider, colliderSize_x, colliderSize_y);
	miscSquare->getTransform()->setPosition(x, y, z);
	miscSquare->getTransform()->setScale(scale);
	return miscSquare;
}

//overload of original misc square generate with collider offset params
std::shared_ptr<MiscSquare> SpawnManager::generateMiscSquare(float x, float y, float z, float scale, string spriteName, bool hasCollider, float colliderSize_x, float colliderSize_y, float colliderOffset_x, float colliderOffset_y)
{
	std::shared_ptr<MiscSquare> miscSquare = GameManager::getInstance()->createGameObject<MiscSquare>(false, spriteName, hasCollider, colliderSize_x, colliderSize_y);
	miscSquare->getComponent<BoxCollider>()->setXOffset(colliderOffset_x);
	miscSquare->getComponent<BoxCollider>()->setYOffset(colliderOffset_y);
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
	auto healthBar = GameManager::getInstance()->createGameObject<HealthBar>(false);
	healthBar->setTrackingPlayer(simpleCharacter);
	simpleCharacter->getTransform()->setPosition(x, y);
	simpleCharacter->getTransform()->setScale(2);
	simpleCharacter->getTransform()->renderRotation = false;

	return simpleCharacter;
}

/*
ishost = are we the host client? If we are, pass true for this, and we will only have senders on the AI.
All non hosts get AI with only listeners. All AI actions are determined by what the host client sees.
*/
std::shared_ptr<Character> SpawnManager::generateAiCharacter(int id, float x, float y, bool isHost)
{

	std::shared_ptr<Character> simpleAi;
	if (isHost) {
		simpleAi = GameManager::getInstance ()->createGameObjectWithId<Character> (false, id, new AiPilot (), beetle);
		std::shared_ptr<Sender> sender = addComponent<Sender> (simpleAi.get(), id);
	}
	else {
		simpleAi = GameManager::getInstance ()->createGameObjectWithId<Character> (false, id, new HostPilot (), beetle);
		std::shared_ptr<Receiver> receiver = addComponent<Receiver> (simpleAi.get(), id);
	}

	auto healthBar = GameManager::getInstance()->createGameObject<HealthBar>(false);
	healthBar->setTrackingPlayer(simpleAi);
	simpleAi->addComponent<Light>(simpleAi.get())->setColor(50, 255, 30)->setSize(4.0f);
	simpleAi->getComponent<Inventory>()->addItem(std::make_shared<BaseLongbow>(
		BaseLongbow::WOODEN_LONGBOW_DAMAGE, BaseLongbow::LONGBOW_CASTING_TIME, BaseLongbow::WOODEN_LONGBOW_IMAGE_NAME,
		"beetle_spit.png", BaseLongbow::WOODEN_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION));
	simpleAi->getTransform()->setPosition(x, y);
	simpleAi->getTransform()->renderRotation = false;
	simpleAi->getTransform()->setScale(2);

	return simpleAi;
}

std::shared_ptr<Character> SpawnManager::generateDummyCharacter(float x, float y)
{
	std::shared_ptr<Character> simpleCharacter = GameManager::getInstance()->createGameObject<Character>(false, new DummyPilot());
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<BaseShortsword>(
		BaseShortsword::WOODEN_SHORTSWORD_DAMAGE, BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME, 
		BaseShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION));
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<BaseChestplate>(
		BaseChestplate::WOODEN_CHESTPLATE_ICON_IMAGE_NAME, BaseChestplate::WOODEN_CHESTPLATE_DAMAGE_MULTIPLIER));
	simpleCharacter->getComponent<Inventory>()->addItem(std::make_shared<BaseHelmet>(
		BaseHelmet::WOODEN_HELMET_ICON_IMAGE, BaseHelmet::WOODEN_HELMET_CRITICAL_RESIST_CHANCE));
	simpleCharacter->getTransform()->setPosition(x, y);
	simpleCharacter->getTransform()->renderRotation = false;

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
	boulder->getTransform()->setZ(2);
	return boulder;
}

std::shared_ptr<Spikes> SpawnManager::generateSpikes(float x, float y)
{
	std::shared_ptr<Spikes> spikes = GameManager::getInstance()->createGameObject<Spikes>(false, Spikes::Direction::North, Spikes::Mode::Enabled, x, y, 2);
	spikes->getTransform()->setPosition(x, y);
	spikes->getTransform()->setZ(2);
	return spikes;
}

std::shared_ptr<DartTrap> SpawnManager::generateDartTrap(float x, float y, DartTrap::Direction direction)
{
	std::shared_ptr<DartTrap> dartTrap = GameManager::getInstance()->createGameObject<DartTrap>(false, direction, DartTrap::Mode::Enabled, x, y, 2);
	dartTrap->getTransform()->setPosition(x, y);
	dartTrap->getTransform()->setZ(2);
	dartTrap->getTransform()->setRotation(direction * 90);
	return dartTrap;
}

std::shared_ptr<GhostCharacter> SpawnManager::generateNetworkGhost(float x, float y, int netId, bool isPlayer)
{
	BasePilot* pilot;
	if (isPlayer) {
		pilot = new GhostPilot();
	}
	else {
		pilot = new GhostReceiverPilot();
	}
	std::shared_ptr<GhostCharacter> ghost = GameManager::getInstance()->createGameObject<GhostCharacter>(false, pilot);
	if (isPlayer) {
		ghost->addComponent<Sender>(ghost.get(), netId);
		Camera::getActiveCamera()->setActiveCamera(GameManager::getInstance()->createGameObject<GhostCamera>(true));
		Camera::getActiveCamera()->addComponent<CameraFollow>(Camera::getActiveCamera().get());
		AudioManager::getInstance()->playMusic(MUSIC_GHOST);
	}
	else {
		ghost->addComponent<Receiver>(ghost.get(), netId);
	}
	ghost->getTransform()->setPosition(x, y);
	ghost->getTransform()->setZ(2);
	return ghost;
}

std::shared_ptr<GhostCharacter> SpawnManager::generateGhost(float x, float y)
{
	std::shared_ptr<GhostCharacter> ghost = GameManager::getInstance()->createGameObject<GhostCharacter>(false, new GhostPilot());
	ghost->addComponent<Light>(ghost.get())->setColor(50, 150, 255)->setSize(3.0f);
	ghost->getTransform()->setPosition(x, y);
	ghost->getTransform()->setZ(2);
	return ghost;
}

std::shared_ptr<SingleDoor> SpawnManager::generateSingleDoor(float x, float y, Door::Direction direction, Door::Mode startState)
{
	auto scale = 9.0f;
	std::shared_ptr<SingleDoor> door = GameManager::getInstance()->createGameObject<SingleDoor>(false, direction, startState, x, y, scale);
	door->getTransform()->setZ(1000);
	door->getTransform()->setScale(10.0f);
	return door;
}

std::shared_ptr<ClientCharacter> SpawnManager::getActivePlayer()
{
	return m_clientPlayer;
}

std::shared_ptr<Throne> SpawnManager::generateThrone(float x, float y)
{
	std::shared_ptr<Throne> throne = GameManager::getInstance()->createGameObject<Throne>(false);
	throne->getTransform()->setPosition(x, y);
	return throne;
}
