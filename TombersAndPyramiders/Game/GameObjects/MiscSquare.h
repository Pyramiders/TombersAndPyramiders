#pragma once

#include "SimpleSprite.h"
#include "ComponentTemplate.h"

//Instance/MovableCharacter
class MiscSquare : public SimpleSprite
{
private:
	////Private Variables

	////Private Methods

public:
	////Public Variables

	////Public Methods
	//The constructor that is called on creation
	MiscSquare(string spriteName, bool hasCollider, float colliderSize_x = 5.0f, float colliderSize_y = 5.0f);
	//The destructor that is called on deletion
	~MiscSquare();

	void onStart() {};
	void onUpdate(int ticks) {}
	void onEnd() {};

};