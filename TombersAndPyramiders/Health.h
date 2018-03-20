#pragma once

#include "SimpleSprite.h"
#include "ComponentTemplate.h"

//Instance/MovableCharacter
class Health : public SimpleSprite
{
private:
	

public:

	Health(string spriteName, bool hasCollider);
	
	~Health();

	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};

};