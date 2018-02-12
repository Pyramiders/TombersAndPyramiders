#pragma once

#include "Updateable.h"
#include "GLHeaders.h"
#include "GameObject.h"
#define GL3_PROTOTYPES 1
#include "Game.h"
#include <vector>
#include <memory>
#include "Scene.h"
#include "SceneManager.h"

class GameManager : public Updateable
{
public:
	GameManager();
	void onStart();
	void onUpdate(int ticks);
	void clearObjectsToRemove();
	void onEnd();
	static GameManager* getInstance();
	void addGameObject(int id, std::shared_ptr<GameObject> obj);
	void removeGameObject(int objectToRemove);
	template <typename T, class... _Types>
	std::shared_ptr<T> createGameObject(bool isGlobal, _Types&&... args)
	{
		std::shared_ptr<T> result = std::make_shared<T>(args...);
		int id = rand() + rand();

		std::shared_ptr<GameObject> gameObject = std::dynamic_pointer_cast<GameObject, T>(result);

		if (gameObject != nullptr)
		{
			gameObject->setInitialState(isGlobal, id);
				
			if (isGlobal)
			{
				GameManager::getInstance()->addGameObject(id, gameObject);
			}
			else
			{
				SceneManager::getInstance()->getCurrentScene()->addGameObject(id, gameObject);
			}
		} 
		else 
		{
			throw "ERROR:GameManager.h:createGameObject:Object created was not a GameObject";
		}

		return result;
	}

private:
	std::vector<int> m_gameObjectsToRemove;
	std::map<int, std::shared_ptr<GameObject>> m_globalGameObjects;
	static GameManager* s_instance;
	bool m_breakLoop = false;
	int m_lastTime = 0;
	//game instance.
	Game* m_game;
	void fpsThrottle(int ticks);
};