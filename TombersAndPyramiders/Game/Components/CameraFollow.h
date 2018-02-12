#pragma once
//This line is needed to avoid circular dependencies
#pragma once

//Include the header file and any other headers that will be required
#include "Component.h"
#include <iostream>
#include <memory>

class CameraFollow : public Component
{
private:
	////Private Variables
	std::shared_ptr<GameObject> m_toFollow;
	float lerp(float t, float a, float b);

public:
	////Public Variables

	////Public Methods
	//The constructor for the component that takes a GameObject
	CameraFollow(GameObject* gameObject);
	//The destructor that is called on deletion
	~CameraFollow();
	//Any public methods you want other Components/GameObjects to have access too
	void setToFollow(std::shared_ptr<GameObject> toFollow);

	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};
};