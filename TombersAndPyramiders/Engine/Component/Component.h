#pragma once
#include "Updateable.h"
#include <memory>

class GameObject;

class Component : public Updateable
{
public:
	Component(GameObject* gameObject);
	virtual ~Component();
	GameObject* getGameObject();
	virtual void onStart() = 0;
	virtual void onUpdate(int ticks) = 0;
	virtual void onEnd() = 0;
	void destroy(std::shared_ptr<GameObject> gameObject);
	void destroy(int gameObjectID);
protected:
	GameObject* gameObject;
};