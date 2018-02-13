#pragma once

#include <memory>
#include "Wall.h"
#include "MiscSquare.h"
#include "MovingSquare.h"
#include "Character.h"
#include "BaseItem.h"
#include "WorldItem.h"

class SpawnManager
{
private:
	static SpawnManager* s_instance;

	SpawnManager();
	~SpawnManager();

public:
	std::shared_ptr<Wall> generateWall(float x, float y, float scale);
	std::shared_ptr<MiscSquare> generateMiscSquare(float x, float y, float scale);
	std::shared_ptr<MovingSquare> generateMovingSquare(float x, float y);
	std::shared_ptr<Character> generatePlayerCharacter(float x, float y);
	std::shared_ptr<WorldItem> generateWorldItem(float x, float y, std::shared_ptr<BaseItem> item);
	static SpawnManager* getInstance();
};