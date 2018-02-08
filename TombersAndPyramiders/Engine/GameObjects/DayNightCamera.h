#pragma once

#include "Camera.h"
#include "FrameBufferObject.h"

class DayNightCamera : public Camera
{
private:
	FrameBufferObject m_regularPass;
	FrameBufferObject m_ambientLighting;

public:
	void virtual applyRenderFilters(SpriteRendererManager* rendererManager);
	void virtual init();
};