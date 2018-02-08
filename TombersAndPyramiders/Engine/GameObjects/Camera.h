#pragma once

#include "GameObject.h"
#include "SpriteRendererManager.h"

class Camera : public GameObject
{
private:
	static Camera* s_activeCamera;
	bool m_init;

protected:
	void virtual init();
	void ensureInit();

public:
	Camera();
	void virtual applyRenderFilters(SpriteRendererManager* rendererManager);
	void virtual notifyInactivity();

	static void setActiveCamera(Camera* camera);
	static Camera* getActiveCamera();
};