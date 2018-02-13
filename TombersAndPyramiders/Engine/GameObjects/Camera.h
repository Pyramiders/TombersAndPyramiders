#pragma once

#include "GameObject.h"
#include "SpriteRendererManager.h"

class Camera : public GameObject
{
private:
	static std::shared_ptr<Camera> s_activeCamera;
	bool m_init;

protected:
	void virtual init();
	void ensureInit();

public:
	Camera();
	void virtual applyRenderFilters(SpriteRendererManager* rendererManager);
	void virtual notifyInactivity();

	static void setActiveCamera(std::shared_ptr<Camera> camera);
	static std::shared_ptr<Camera> getActiveCamera();

	bool isOnScreen(Transform* transform);
	bool isOnScreen(float transformX, float transformY, float transformScale);
};