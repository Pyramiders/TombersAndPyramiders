#pragma once

#include <memory>
#include "Wall.h"
#include "MiscSquare.h"
#include "MovingSquare.h"
#include "Character.h"
#include "BaseItem.h"
#include "WorldItem.h"
#include "HostCharacter.h"
#include "ClientCharacter.h"
#include "NetworkCharacter.h"
#include "GhostCharacter.h"
#include "Boulder.h"
#include "SingleDoor.h"
#include "Obstacles/Spikes.h"
#include "Obstacles/DartTrap.h"
#include "Throne.h"

class SpawnManager : public GameObject
{
public:
	SpawnManager();
	~SpawnManager();
	std::shared_ptr<MiscSquare> generateMiscSquare(float x, float y, float z, float scale, string spriteName, bool hasCollider, float colliderSize_x, float colliderSize_y, float colliderOffset_x, float colliderOffset_y);
	std::shared_ptr<MiscSquare> generateMiscSquare(float x, float y, float z, float scale, string spriteName, bool hasCollider, float colliderSize_x = 5, float colliderSize_y = 5);
	//std::shared_ptr<Wall> generateWall(float x, float y, float scale);
	//std::shared_ptr<MiscSquare> generateMiscSquare(float x, float y, float scale);
	std::shared_ptr<MovingSquare> generateMovingSquare(float x, float y);
	std::shared_ptr<Character> generatePlayerCharacter(float x, float y);
	std::shared_ptr<Character> generateAiCharacter (int id, float x, float y, bool isHost = false);
	//std::shared_ptr<Character> generateBossAiCharacter(int id, float x, float y, bool isHost = false);
	std::shared_ptr<WorldItem> generateWorldItem(float x, float y, std::shared_ptr<BaseItem> item);
	std::shared_ptr<Character> generateDummyCharacter(float x, float y);
	std::shared_ptr<GhostCharacter> generateGhost(float x, float y);
	std::shared_ptr<GhostCharacter> generateNetworkGhost(float x, float y, int netId, bool isPlayer);
	std::shared_ptr<Boulder> generateBoulder(float x, float y); 
	std::shared_ptr<Spikes> generateSpikes(float x, float y); 
	std::shared_ptr<DartTrap> generateDartTrap(float x, float y, DartTrap::Direction direction);
	std::shared_ptr<SingleDoor> generateSingleDoor(float x, float y, Door::Direction direction, Door::Mode startState);
	std::vector<shared_ptr<Character>> allPlayers;

	std::shared_ptr<HostCharacter> generateHostCharacter(int id, float x, float y);
	std::shared_ptr<ClientCharacter> generatePlayerCharacter (int id, float x, float y);
	std::shared_ptr<NetworkCharacter> generateNetworkCharacter (int id, float x, float y);
	std::shared_ptr<Throne> generateThrone(float x, float y);

	void sendStartPacket();
	void listenForStartPacket ();
	void stopListeningForStartPacket ();

	static std::shared_ptr<SpawnManager> getInstance();

	std::shared_ptr<ClientCharacter> getActivePlayer();

private:
	static std::shared_ptr<SpawnManager> s_instance;
	std::shared_ptr<ClientCharacter> m_clientPlayer;
	int m_startPacketListenerID;
};