#pragma once

#include "Camera.h"
#include "FrameBufferObject.h"

class FogOfWarCamera : public Camera
{
private:
	FrameBufferObject m_regularPass;
	FrameBufferObject m_fogOfWarPass;
	GLuint m_fogOfWarMask;

public:
	void virtual applyRenderFilters(SpriteRendererManager* rendererManager);
	void virtual init();
	void updateFogOfWarMask();
};