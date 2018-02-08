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
	MiscSquare();
	//The destructor that is called on deletion
	~MiscSquare();

	void onStart() {};
	void onUpdate(int ticks) {}
	void onEnd() {};

};