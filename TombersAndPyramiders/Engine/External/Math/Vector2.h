#pragma once
#define _USE_MATH_DEFINES

#include <cmath>

class Vector2
{
private:
	float m_x;
	float m_y;
	float m_magnitude;
	float m_rotation; //0 is right facing not implemented 
public:
	Vector2();
	Vector2(float x, float y);

	static Vector2* convertAngleToVector(float angle);

	static float dotProduct(Vector2* a, Vector2* b);

	void normalize();
	void translate(float xOffset, float yOffset);
	void rotate(float angle);
	float checkAngle(float angle);
	void rotateFromOrigin(Vector2 origin, float angle);

	float getMagnitude();

	void setX(float value);
	float getX();

	void setY(float value);
	float getY();

	void rotateVector(float radians);
	
	/**
	*	returns the rotation of the current vector in degrees
	*	i.e. if m_x = 0 and m_y = 1 it will return 270 
	*/
	float getRotationInDegrees();

	Vector2* operator*(float value);
	Vector2* operator/(float value);
	Vector2* operator-(Vector2 v);
	Vector2* operator-();
	Vector2* operator+(Vector2 v);
};