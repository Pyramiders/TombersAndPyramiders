#pragma once
#include "ComplexSprite.h"

class Room : public ComplexSprite {
private:
	std::shared_ptr<ComplexSpriteInfo> generateComplexSpriteInfo();
public:
	int m_xCoord;
	int m_yCoord;
	int m_width;
	int m_height;
	int m_scale;
	int m_level;
	int m_spawnX;
	int m_spawnY;
	bool m_exit;
	bool m_spawn;

	std::vector<int> doorsX;
	std::vector<int> doorsY;

	Room(int width, int height, int xCoord, int yCoord, bool exit, bool spawn, int level);
	void draw();

};