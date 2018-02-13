#pragma once

#include "GameObject.h"
#include "ComponentTemplate.h"

//Instance/MovableCharacter
class GameObjectTemplate : public GameObject
{
private:
	////Private Variables

	////Private Methods

public:
	////Public Variables

	////Public Methods
	//The constructor that is called on creation
	GameObjectTemplate();
	//The destructor that is called on deletion
	~GameObjectTemplate();
	//Any public methods you want other Components/GameObjects to have access too
	void exampleMethod();

	void onStart() {};
	void onUpdate(int ticks) {};
	void onEnd() {};

};