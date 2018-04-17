#pragma once

#include "Camera.h"
#include "FrameBufferObject.h"

class GhostCamera : public Camera
{
private:
	FrameBufferObject m_regularPass;

public:
	void virtual applyRenderFilters(SpriteRendererManager* rendererManager);
	void virtual init();
};