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
		offset = new Vector2(5.0f, 3.0f);
		break;
	case Door::East:
		offset = new Vector2(5.0f, 3.0f);
		break;
	case Door::North:
		offset = new Vector2(1.0f, 5.0f);
		break;
	case Door::South:
		offset = new Vector2(1.0f, 5.0f);
		break;
	default:
		throw "ERROR::SingleDoor::createColliderOffset:: Not a valid direciton";
	}
	return offset;
}

std::shared_ptr<ComplexSpriteinfo> SingleDoor::createSpriteInfo(Direction direction)
{
	std::shared_ptr<ComplexSpriteinfo> spriteInfo = std::make_shared<ComplexSpriteinfo>();
	switch (direction)
	{
	case Door::West:
		spriteInfo->addInfo("stoneWallGateOpen_W.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateClosed_W.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateOpen_W.png", 1, 1); //Opening
		spriteInfo->addInfo("stoneWallGateClosed_W.png", 1, 1); //Closing
		break;
	case Door::East:
		spriteInfo->addInfo("stoneWallGateOpen_E.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateClosed_E.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateOpen_E.png", 1, 1); //Opening
		spriteInfo->addInfo("stoneWallGateClosed_E.png", 1, 1); //Closing
		break;
	case Door::North:
		spriteInfo->addInfo("stoneWallGateOpen_N.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateClosed_N.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateOpen_N.png", 1, 1); //Opening
		spriteInfo->addInfo("stoneWallGateClosed_N.png", 1, 1); //Closing
		break;
	case Door::South:
		spriteInfo->addInfo("stoneWallGateOpen_S.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateClosed_S.png", 1, 1);
		spriteInfo->addInfo("stoneWallGateOpen_S.png", 1, 1); //Opening
		spriteInfo->addInfo("stoneWallGateClosed_S.png", 1, 1); //Closing
		break;
	default:
		break;
	}
	return spriteInfo;
}