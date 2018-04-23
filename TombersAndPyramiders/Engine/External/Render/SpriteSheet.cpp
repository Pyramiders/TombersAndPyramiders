#include "SpriteSheet.h"
#include <iostream>

SpriteSheet::SpriteSheet(GLuint textureBufferID, int columnCount, int rowCount, int skipLastFrames, int startIndex)
{
	this->m_textureBufferID = textureBufferID;
	this->m_columnCount = columnCount;
	this->m_rowCount = rowCount;
	this->m_currentFrame = startIndex;
	this->m_skipLastFrames = skipLastFrames;
	this->m_minFrame = -1;
	this->m_maxFrame = -1;
	reloadTextCoordinates();
}

SpriteSheet::~SpriteSheet()
{

}

void SpriteSheet::bindTextCoordinates(GLuint glCBO)
{
	glBindBuffer(GL_ARRAY_BUFFER, glCBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textCoordinates), m_textCoordinates.data(), GL_STATIC_DRAW);
}

std::array<GLfloat, 8> SpriteSheet::getTextureCoordinates()
{
	return m_textCoordinates;
}

GLuint SpriteSheet::getTextureBufferID()
{
	return m_textureBufferID;
}

void SpriteSheet::nextIndex()
{
	if (m_minFrame == -1)
	{
		int maxIndex = m_columnCount * m_rowCount - 1;
		if (++m_currentFrame > maxIndex - m_skipLastFrames)
		{
			m_currentFrame = 0;
		}
	}
	else
	{
		if (++m_currentFrame > m_maxFrame - m_skipLastFrames)
		{
			m_currentFrame = m_minFrame;
		}
	}

	reloadTextCoordinates();
}

void SpriteSheet::resetIndex()
{
	if (m_minFrame == -1)
	{
		m_currentFrame = 0;
	}
	else
	{
		m_currentFrame = m_minFrame;
	}
	reloadTextCoordinates();
}

/*
	0 / 2 = 0
	1 / 2 = 0
	2 / 2 = 1
	3 / 2 = 1
	4 / 2 = 2
*/

void SpriteSheet::reloadTextCoordinates()
{
	float testOffset = 0.01f;

	float columnPercent = 1.0f / ((float)m_columnCount); //1/2 = .5%, so 0%/50% or 0/1 out of 2
	int columnIndex = m_currentFrame % m_columnCount; //if index == 3, 3%2=1, index 3 is 2nd column
	float startX = (float)columnIndex * (float)columnPercent; //1 * 0.5 = 0.5f is start
	float endX = startX + columnPercent; //0.5f + 0.5f = 1.0f
	float rowPercent = 1.0f / ((float)m_rowCount);
	int rowIndex = m_currentFrame / m_columnCount; //if index == 3, 3%2=1, index 3 is in 2nd row
	float startY = 1 - (float)rowIndex * (float)rowPercent; //1 - 0.5f
	float endY = startY - rowPercent;
	startY = 1 - startY;
	endY = 1 - endY;
	startX += testOffset;
	endX -= testOffset;
	//std::cout << "(" << startX << "," << startY << "),(" << endX << "," << endY << ")" << std::endl;
	m_textCoordinates = {
		endX, startY,  //Top Right
		endX, endY,    //Bottom Right
		startX, endY,  //Bottom Left
		startX, startY //Top Left
	};
}

int SpriteSheet::getRowCount()
{
	return m_rowCount;
}

int SpriteSheet::getColumnCount()
{
	return m_columnCount;
}

int SpriteSheet::getCurrentIndex()
{
	return m_currentFrame;
}


void SpriteSheet::setCurrentIndex(int currentIndex)
{
	m_currentFrame = currentIndex;
}

void SpriteSheet::changeAnimation(int minFrame, int maxFrame)
{
	m_minFrame = minFrame;
	m_maxFrame = maxFrame;

	resetIndex();
};
