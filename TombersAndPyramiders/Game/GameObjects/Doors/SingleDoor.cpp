#include "SingleDoor.h"

SingleDoor::SingleDoor(Door::Direction direction, Door::Mode mode, float startX, float startY, float scale) : Door(createSpriteInfo(direction), createColliderOffset(direction, scale), direction, mode, startX, startY, scale)
{
}

Vector2* SingleDoor::createColliderOffset(Direction direction, float scale)
{
	Vector2* offset;
	switch(direction)
	{
	case Door::West:
		offset = new Vector2(7.0f, 3.0f);
		break;
	case Door::East:
		offset = new Vector2(7.0f, 3.0f);
		break;
	case Door::North:
		offset = new Vector2(1.0f, 7.0f);
		break;
	case Door::South:
		offset = new Vector2(1.0f, 7.0f);
		break;
	default:
		throw "ERROR::SingleDoor::createColliderOffset:: Not a valid direciton";
	}
	return offset;
}

std::shared_ptr<ComplexSpriteInfo> SingleDoor::createSpriteInfo(Direction direction)
{
	std::shared_ptr<ComplexSpriteInfo> spriteInfo = std::make_shared<ComplexSpriteInfo>();
	switch (direction)
	{
	case Door::West:
		spriteInfo->addSprite("stoneWallGateOpen_W.png", "stoneWallGateOpen_W", 1, 1);
		spriteInfo->addSprite("stoneWallGateClosed_W.png", "stoneWallGateClosed_W", 1, 1);
		spriteInfo->addSprite("stoneWallGateOpen_W.png", "stoneWallGateOpen_W", 1, 1); //Opening
		spriteInfo->addSprite("stoneWallGateClosed_W.png", "stoneWallGateClosed_W", 1, 1); //Closing
		break;
	case Door::East:
		spriteInfo->addSprite("stoneWallGateOpen_E.png", "stoneWallGateOpen_E", 1, 1);
		spriteInfo->addSprite("stoneWallGateClosed_E.png", "stoneWallGateClosed_E", 1, 1);
		spriteInfo->addSprite("stoneWallGateOpen_E.png", "stoneWallGateOpen_E", 1, 1); //Opening
		spriteInfo->addSprite("stoneWallGateClosed_E.png", "stoneWallGateClosed_E", 1, 1); //Closing
		break;
	case Door::North:
		spriteInfo->addSprite("stoneWallGateOpen_N.png", "stoneWallGateOpen_N", 1, 1);
		spriteInfo->addSprite("stoneWallGateClosed_N.png", "stoneWallGateClosed_N", 1, 1);
		spriteInfo->addSprite("stoneWallGateOpen_N.png", "stoneWallGateOpen_N", 1, 1); //Opening
		spriteInfo->addSprite("stoneWallGateClosed_N.png", "stoneWallGateClosed_N", 1, 1); //Closing
		break;
	case Door::South:
		spriteInfo->addSprite("stoneWallGateOpen_S.png", "stoneWallGateOpen_S", 1, 1);
		spriteInfo->addSprite("stoneWallGateClosed_S.png", "stoneWallGateClosed_S", 1, 1);
		spriteInfo->addSprite("stoneWallGateOpen_S.png", "stoneWallGateOpen_S", 1, 1); //Opening
		spriteInfo->addSprite("stoneWallGateClosed_S.png", "stoneWallGateClosed_S", 1, 1); //Closing
		break;
	default:
		break;
	}
	return spriteInfo;
}