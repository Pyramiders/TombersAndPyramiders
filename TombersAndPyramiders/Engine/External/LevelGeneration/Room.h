#pragma once
#include "ComplexSprite.h"

class Room : public ComplexSprite {
private:
	std::shared_ptr<ComplexSpriteinfo> generateComplexSpriteInfo();
public:
	int m_xCoord;
	int m_yCoord;
	int m_width;
	int m_height;
	int m_scale;
	bool m_exit;

	std::vector<int> doorsX;
	std::vector<int> doorsY;

	Room(int width, int height, int xCoord, int yCoord, bool exit);
	void draw();

};