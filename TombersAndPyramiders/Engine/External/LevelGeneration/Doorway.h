#pragma once

class Doorway {
private:

public:
	int m_xCoord;
	int m_yCoord;
	int m_width;
	int m_height;

	Doorway(int width, int height, int xCoord, int yCoord);
};