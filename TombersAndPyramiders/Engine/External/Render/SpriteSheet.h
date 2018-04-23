#pragma once

#include "GLHeaders.h"
#include "ISprite.h"
#include <array>
#include <iostream>

/*
TODO: With messaging system, create a "SpriteHUB" object that extends ISprite.
This SpriteHUB will let you set as many sprites as you want, with info on what event to trigger, or something like that.
Basically, easy system for switching between sprites
*/

class SpriteSheet : public ISprite
{
private:
	GLuint m_textureBufferID;
	int m_currentFrame;
	int m_columnCount;
	int m_rowCount;
	int m_skipLastFrames;

	// These are used to run animations
	int m_minFrame;
	int m_maxFrame;

	void reloadTextCoordinates();
	std::array<GLfloat, 8> m_textCoordinates;

public:
	SpriteSheet(GLuint textureBufferID, int columnCount, int rowCount, int skipLastFrames = 0, int startIndex = 0);
	~SpriteSheet();
	virtual void bindTextCoordinates(GLuint glCBO);
	virtual GLuint getTextureBufferID();
	virtual std::array<GLfloat, 8> getTextureCoordinates();
	void nextIndex();
	void resetIndex();
	int getRowCount();
	int getColumnCount();
	int getCurrentIndex();
	void setCurrentIndex(int currentIndex);
	void changeAnimation(int minFrame, int maxFrame);
};