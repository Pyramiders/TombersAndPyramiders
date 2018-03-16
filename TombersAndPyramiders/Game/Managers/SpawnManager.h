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

class SpawnManager : public GameObject
{
public:
	SpawnManager();
	~SpawnManager();
	std::shared_ptr<MiscSquare> generateMiscSquare(float x, float y, float z, float scale, string spriteName, bool hasCollider);
	//std::shared_ptr<Wall> generateWall(float x, float y, float scale);
	//std::shared_ptr<MiscSquare> generateMiscSquare(float x, float y, float scale);
	std::shared_ptr<MovingSquare> generateMovingSquare(float x, float y);
	std::shared_ptr<Character> generatePlayerCharacter(float x, float y);
	std::shared_ptr<Character> generateAiCharacter(float x, float y);
	std::shared_ptr<WorldItem> generateWorldItem(float x, float y, std::shared_ptr<BaseItem> item);
	std::shared_ptr<Character> generateDummyCharacter(float x, float y);

	std::shared_ptr<HostCharacter> generateHostCharacter(int id, float x, float y);
	std::shared_ptr<ClientCharacter> generatePlayerCharacter (int id, float x, float y);
	std::shared_ptr<NetworkCharacter> generateNetworkCharacter (int id, float x, float y);


	void sendStartPacket();
	void listenForStartPacket ();
	void stopListeningForStartPacket ();

	static std::shared_ptr<SpawnManager> getInstance();

private:
	static std::shared_ptr<SpawnManager> s_instance;
	int m_startPacketListenerID;
};