#pragma once

#include "GLHeaders.h"
#include <array>

class ISprite
{
public:
	virtual void bindTextCoordinates(GLuint glCBO) = 0;
	virtual GLuint getTextureBufferID() = 0;
	virtual std::array<GLfloat, 8> getTextureCoordinates() = 0;
};