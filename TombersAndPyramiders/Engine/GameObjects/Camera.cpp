#include "Camera.h"

Camera* Camera::s_activeCamera = new Camera();

Camera::Camera() : GameObject(true)
{
	m_init = false;
}

void Camera::applyRenderFilters(SpriteRendererManager* rendererManager)
{
	rendererManager->renderPass();
}

void Camera::setActiveCamera(Camera* camera)
{
	s_activeCamera->notifyInactivity();
	s_activeCamera = camera;
}

Camera* Camera::getActiveCamera()
{
	return s_activeCamera;
}

void Camera::notifyInactivity()
{
	destroy(this);
}

void Camera::ensureInit()
{
	if (!m_init)
	{
		init();
		m_init = true;
	}
}

void Camera::init() {}