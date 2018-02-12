#include "Vector2.h"

Vector2::Vector2()
{
	m_x = 0;
	m_y = 0;
}

Vector2::Vector2(float x, float y) : m_x(x), m_y(y)
{
}

void Vector2::setX(float value)
{
	m_x = value;
}

float Vector2::getX()
{
	return m_x;
}

void Vector2::setY(float value)
{
	m_y = value;
}

float Vector2::getY()
{
	return m_y;
}

float Vector2::getMagnitude()
{
	m_magnitude = sqrt(pow(m_x, 2) + pow(m_y, 2));
	return m_magnitude;
}

void Vector2::normalize()
{
	getMagnitude();
	m_x /= m_magnitude;
	m_y /= m_magnitude;
}

void Vector2::translate(float xOffset, float yOffset)
{
	m_x += xOffset;
	m_y += yOffset;
}

void Vector2::rotate(float angle)
{
	float radians;
	float xTemp, yTemp;
	radians = angle * -1 * (M_PI / 180);
	xTemp = m_x;
	yTemp = m_y;
	m_x = xTemp * cos(radians) + yTemp * -sin(radians);
	m_y = xTemp * sin(radians) + yTemp * cos(radians);
}

float Vector2::checkAngle(float angle)
{
	float result;
	result = angle;
	if (result < 0 || result > 360)
	{
		while (result > 360)
		{
			result -= 360;
		}
		while (result < 0)
		{
			result += 360;
		}
	}
	return result;
}

void Vector2::rotateFromOrigin(Vector2 origin, float angle)
{
	float xOffset;
	float yOffset;
	xOffset = -origin.getX();
	yOffset = -origin.getY();
	translate(xOffset, yOffset);
	rotate(angle);
	translate(origin.getX(), origin.getY());
}

Vector2* Vector2::convertAngleToVector(float angle)
{
	Vector2* result = new Vector2();
	result->setX(0);
	result->setY(1);
	result->rotate(angle);
	return result;
}

float Vector2::dotProduct(Vector2* a, Vector2* b)
{
	return a->getX() * b->getX() + a->getY() * b->getY();
}

//OPERATORS

Vector2* Vector2::operator*(float value)
{
	m_x *= value;
	m_y *= value;
	return this;
}

Vector2* Vector2::operator/(float value)
{
	m_x /= value;
	m_y /= value;
	return this;
}

Vector2* Vector2::operator+(Vector2 v)
{
	m_x += v.getX();
	m_y += v.getY();
	return this;
}

Vector2* Vector2::operator-(Vector2 v)
{
	m_x -= v.getX();
	m_y -= v.getY();
	return this;
}

Vector2* Vector2::operator-()
{
	m_x = -m_x;
	m_y = -m_y;
	return this;
}

void Vector2::rotateVector(float radians)
{
	float tempCos = cos(radians);
	float tempSin = sin(radians);
	m_x = tempCos * m_x - tempSin * m_y;
	m_y = tempSin * m_x + tempCos * m_y;
}

float Vector2::getRotationInDegrees() {
	if (m_x > 0 && m_y <= 0) {
		m_rotation = atan(-m_y / m_x);
	}
	else if (m_x <= 0 && m_y < 0) {
		m_rotation = atan(-m_x / -m_y) + M_PI / 2;
	}
	else if (m_x < 0 && m_y >= 0){
		m_rotation = atan(-m_y / m_x) + M_PI;
	}
	else if (m_x >= 0 && m_y > 0) {
		m_rotation = atan(m_x / m_y) + 3 * M_PI / 2;
	}
	else {
		m_rotation = 0;
	}
	return (m_rotation * 180 / M_PI);
}
