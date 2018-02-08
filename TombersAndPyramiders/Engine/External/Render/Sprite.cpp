#include "Sprite.h"

Sprite::Sprite(GLuint textureBufferID)
{
	this->m_textureBufferID = textureBufferID;
	m_textCoordinates = {
		1.0f, 1.0f,  //Top Right
		1.0f, 0.0f,  //Bottom Right
		0.0f, 0.0f,  //Bottom Left
		0.0f, 1.0f   //Top Left
	};
}

Sprite::~Sprite()
{

}

void Sprite::bindTextCoordinates(GLuint glCBO)
{
	glBindBuffer(GL_ARRAY_BUFFER, glCBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textCoordinates), m_textCoordinates.data(), GL_STATIC_DRAW);
}

std::array<GLfloat, 8> Sprite::getTextureCoordinates()
{
	return m_textCoordinates;
}

GLuint Sprite::getTextureBufferID()
{
	return m_textureBufferID;
}