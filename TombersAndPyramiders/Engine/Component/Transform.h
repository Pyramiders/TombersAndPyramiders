#pragma once

#include <GL/glew.h>
#include <math.h>
#include "HelperFunctions.h"
#include <iostream>
#include "Component.h"
#include <memory>

class Transform : public Component
{
private:
	float m_x;
	float m_y;
	float m_z;
	float m_rotation;
	float m_scale;
	std::shared_ptr<GLfloat> m_values;

public:
	Transform(GameObject* gameObject);
	void addTranslation(float xToAdd, float yToAdd);

	void onStart() {};
	void onUpdate(int ticks) {};
	void onEnd() {};

	void addX(float xToAdd);
	void addY(float yToAdd);
	void addZ(float zToAdd);
	void setX(float newX);
	float getX();

	//__declspec (property (put = setY, get = getY)) float y;
	void setY(float newY);

	void setZ(float zToSet);
	void setPosition(float newX, float newY);
	void setPosition(float newX, float newY, float newZ);
	void addRotation(float byDegrees);
	void addScale(float scaleToAdd);
	void setScale(float newScale);
	float getY();
	float getZ();
	float getScale();

	//__declspec (property (put = setRotation, get = getRotation)) float rotation;
	void setRotation(float newAngle);
	float getRotation();
	operator GLfloat*();
	template< typename T >

	struct array_deleter
	{
		void operator ()(T const * p)
		{
			delete[] p;
		}
	};
};