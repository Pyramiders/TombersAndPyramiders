#pragma once

#include "Updateable.h"
#include "GLHeaders.h"
#include "GameObject.h"
#define GL3_PROTOTYPES 1
#include "Scene.h"
#include "Game.h"
#include <vector>

class GameManager : public Updateable
{
public:
	GameManager();
	void onStart();
	void onUpdate(int ticks);
	void clearObjectsToRemove();
	void onEnd();
	static GameManager* getInstance();

	void addGameObject(int id, GameObject* obj);
	void removeGameObject(GameObject* objectToRemove);

private:
	std::vector<GameObject*> m_gameObjectsToRemove;
	std::map<int, std::shared_ptr<GameObject>> m_globalGameObjects;
	static GameManager* s_instance;
	bool m_breakLoop = false;
	int m_lastTime = 0;
	//game instance.
	Game* m_game;
	void fpsThrottle(int ticks);
};