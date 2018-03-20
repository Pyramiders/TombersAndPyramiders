#pragma once

class Corridor {
private:

public:
	int m_xCoord;
	int m_yCoord;
	int m_scale;
	int m_width;
	int m_height;

	Corridor(int width, int height, int xCoord, int yCoord);
	void draw();
};