#pragma once

#include "GLHeaders.h"
#include "ISprite.h"
#include <array>
#include <iostream>


class Sprite : public ISprite
{
private:
	GLuint m_textureBufferID;
	std::array<GLfloat, 8> m_textCoordinates;

public:
	Sprite(GLuint textureBufferID);
	~Sprite();
	virtual void bindTextCoordinates(GLuint glCBO);
	virtual GLuint getTextureBufferID();
	virtual std::array<GLfloat, 8> getTextureCoordinates();
};