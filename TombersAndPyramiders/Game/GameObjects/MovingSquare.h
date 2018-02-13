#pragma once

#include "SimpleSprite.h"
#include "ComponentTemplate.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

//Instance/MovableCharacter
class MovingSquare : public SimpleSprite
{
private:
	////Private Variables
	std::shared_ptr<BoxCollider> m_boxCollider = nullptr;
	std::shared_ptr<CircleCollider> m_circleCollider = nullptr;

	////Private Methods

public:
	////Public Variables

	////Public Methods
	//The constructor that is called on creation
	MovingSquare();
	//The destructor that is called on deletion
	~MovingSquare();

	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};

};