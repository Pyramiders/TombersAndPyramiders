#pragma once

#include <memory>
#include <vector>
#include <map>
#include "Updateable.h"

class GameObject;

class Scene : public Updateable
{
private:
	std::vector<int> m_idsToRemove;

public:
	std::map<int, std::shared_ptr<GameObject>> sceneObjects;

	//Called on unpausing from the SceneManager's scene stack.
	virtual void onResume() = 0;

	//Called by manager, do not override, used to update game objects in scene.
	void onObjectsUpdate(int ticks);

	//Called when pausing the scene when another scene is added on top of SceneManager's stack.
	virtual void onPause() = 0;

	//Add a game object that belongs to this scene. Global objects will not be here, but in Game Manager.
	void addGameObject(int id, std::shared_ptr<GameObject> obj);

	//Remove a game object from the scene
	void removeGameObject(int id);

	void purge();
};