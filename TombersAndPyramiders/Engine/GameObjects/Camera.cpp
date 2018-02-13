#include "Camera.h"
#include <memory>
#include "GameManager.h"
#include "HelperFunctions.h"

std::shared_ptr<Camera> Camera::s_activeCamera = GameManager::getInstance()->createGameObject<Camera>(true);

Camera::Camera() : GameObject()
{
	m_init = false;
}

void Camera::applyRenderFilters(SpriteRendererManager* rendererManager)
{
	rendererManager->renderPass();
}

void Camera::setActiveCamera(std::shared_ptr<Camera> camera)
{
	s_activeCamera->notifyInactivity();
	s_activeCamera = camera;
}

std::shared_ptr<Camera> Camera::getActiveCamera()
{
	return s_activeCamera;
}

void Camera::notifyInactivity()
{
	destroy(s_activeCamera);
	s_activeCamera = nullptr;
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

bool Camera::isOnScreen(float transformX, float transformY, float transformScale)
{
	Transform* cameraTransform = s_activeCamera->getTransform();
	return (abs(transformX - cameraTransform->getX()) * 2 < (transformScale + getGameWidth())) &&
		(abs(transformY - cameraTransform->getY()) * 2 < (transformScale + getGameHeight()));
}

bool Camera::isOnScreen(Transform* transform)
{
	return isOnScreen(transform->getX(), transform->getY(), transform->getScale());
}