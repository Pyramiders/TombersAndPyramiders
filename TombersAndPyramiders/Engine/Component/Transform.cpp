#include "Transform.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"

Transform::operator GLfloat*()
{
	if (m_values == nullptr)
	{
		m_values = std::shared_ptr<GLfloat> ( new GLfloat[16]{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		}, array_deleter<GLfloat>());
	}
	else if (m_values == NULL)
	{
		return nullptr;
	}

	float scaleRotCos = m_scale / GAME_WIDTH * 2.0 * cos(-m_rotation * renderRotation * 3.14159 / 180.0);
	float scaleRotSin = m_scale / GAME_WIDTH * 2.0 * sin(-m_rotation * renderRotation * 3.14159 / 180.0);

	Transform cameraTransform = (*(*Camera::getActiveCamera()).getTransform());

	float glX = m_x - cameraTransform.getX(); //x = 5
	float glY = m_y - cameraTransform.getY(); //y = 5

	worldPositionToOpenGLPosition(&glX, &glY);

	m_values.get()[0] = scaleRotCos;
	m_values.get()[1] = -scaleRotSin;
	m_values.get()[4] = scaleRotSin;
	m_values.get()[5] = scaleRotCos;
	m_values.get()[12] = glX;
	m_values.get()[13] = glY;

	return m_values.get();
}

Transform::Transform(GameObject* gameObject) : Component(gameObject)
{
	m_scale = 1.0f;
	m_x = 0.0f;
	m_y = 0.0f;
	m_rotation = 0.0f;
	m_values = nullptr;
}

float Transform::getDistance(Transform* otherTransform)
{
	Vector2 theirPos = Vector2(otherTransform->getX(), otherTransform->getY());
	Vector2 ourPos = Vector2(getX(), getY());
	Vector2 diffPos = *(theirPos - ourPos);
	return sqrtf(diffPos.getX() * diffPos.getX() + diffPos.getY() * diffPos.getY());
}

void Transform::addTranslation(float xToAdd, float yToAdd)
{
	m_x += xToAdd;
	m_y += yToAdd;
}

void Transform::setPosition(float newX, float newY)
{
	m_x = newX;
	m_y = newY;
}

void Transform::setPosition(float newX, float newY, float newZ)
{
	m_x = newX;
	m_y = newY;
	m_z = newZ;
}

void Transform::addX(float xToAdd)
{
	m_x += xToAdd;
}

void Transform::addY(float yToAdd)
{
	m_y += yToAdd;
}

void Transform::addZ(float zToAdd)
{
	m_z += zToAdd;
}

void Transform::setX(float newX)
{
	m_x = newX;
}

void Transform::setY(float newY)
{
	m_y = newY;
}

void Transform::setZ(float newZ)
{
	m_z = newZ;
}

void Transform::addRotation(float byDegrees)
{
	m_rotation += byDegrees;
}

void Transform::setRotation(float newAngle)
{
	m_rotation = newAngle;
}

void Transform::setScale(float newScale)
{
	m_scale = newScale;
}

float Transform::getX()
{
	return m_x;
}

float Transform::getY()
{
	return m_y;
}

float Transform::getZ()
{
	return m_z;
}

float Transform::getRotation()
{
	return m_rotation;
}

float Transform::getScale()
{
	return m_scale;
}

void Transform::addScale(float toAdd)
{
	m_scale += toAdd;
}