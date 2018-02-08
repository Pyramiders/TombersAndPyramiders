#pragma once

#include "GLHeaders.h"
#include "SharedConstants.h"

class FrameBufferObject
{
private:
	int m_width;
	int m_height;
	GLuint m_frameBuffer;
	GLuint m_texture;

public:
	FrameBufferObject(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
	void cleanUp();
	void bindFrameBuffer();
	void unbindFrameBuffer();
	void bindToRead();
	GLuint getTexture();
	void createFrameBuffer();
	void createTextureAttachment();
	void init();
};
