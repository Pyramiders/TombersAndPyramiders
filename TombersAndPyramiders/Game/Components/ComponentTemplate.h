//This line is needed to avoid circular dependencies
#pragma once

//Include the header file and any other headers that will be required
#include "Component.h"
#include <iostream>

class ComponentTemplate : public Component
{
private:
	////Private Variables

	////Private Methods

public:
	////Public Variables

	////Public Methods
	//The constructor for the component that takes a GameObject
	ComponentTemplate(GameObject* gameObject);
	//The destructor that is called on deletion
	~ComponentTemplate();
	//Any public methods you want other Components/GameObjects to have access to
	void exampleMethod();

	void onStart() {};
	void onUpdate(int ticks) {};
	void onEnd() {};
};