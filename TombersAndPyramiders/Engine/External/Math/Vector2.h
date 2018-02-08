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

	//__declspec (property (get = getMagnitude)) float magnitude;
	float getMagnitude();

	//__declspec (property (put = setX, get = getX)) float x;
	void setX(float value);
	float getX();

	//__declspec (property (put = setY, get = getY)) float y;
	void setY(float value);
	float getY();

	void rotateVector(float radians);

	Vector2* operator*(float value);
	Vector2* operator/(float value);
	Vector2* operator-(Vector2 v);
	Vector2* operator-();
	Vector2* operator+(Vector2 v);
};