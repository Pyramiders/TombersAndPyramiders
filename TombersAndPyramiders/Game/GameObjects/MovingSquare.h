#pragma once

#include "SimpleSprite.h"
#include "ComponentTemplate.h"

//Instance/MovableCharacter
class MovingSquare : public SimpleSprite
{
private:
	////Private Variables

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