#include "GameManager.h"
#include "InputManager.h"
#include "SpriteRendererManager.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "MessageManager.h"
#include "NetworkingManager.h"
#include "SceneManager.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "GarbageCollection.h"
#include <memory>

GameManager* GameManager::s_instance;

GameManager* GameManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new GameManager();
	return s_instance;
}

GameManager::GameManager()
{

}

void GameManager::onStart()
{

	m_lastTime = SDL_GetTicks();
	m_game = new Game();
	m_game->onStart();
	PhysicsManager::getInstance()->onStart();
	while (!m_breakLoop)
	{
		int curTime = SDL_GetTicks();
		int ticks = curTime - m_lastTime;
		m_lastTime = curTime;
		//update system managers then.
		onUpdate(ticks);
		//update game.
		SceneManager::getInstance()->updateScene(ticks);

		clearObjectsToRemove();

		fpsThrottle(ticks);
	}
}

void GameManager::onUpdate(int ticks)
{

	//Handle SDL Events
	InputManager::getInstance()->updateKeys();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_breakLoop = true;
			break;
		default:
			InputManager::getInstance()->handlePolledEvent(event);
			break;
		}
	}

	if (NetworkingManager::getInstance()->isConnected())
	{
		std::string tmp;
		while (NetworkingManager::getInstance()->getMessage(tmp))
		{
			NetworkingManager::getInstance()->handleParsingEvents(tmp);
		}

		NetworkingManager::getInstance()->sendQueuedEvents();
	}

	SpriteRendererManager::getInstance()->onUpdate(ticks);
	PhysicsManager::getInstance()->onUpdate(ticks);

	for (std::map<int, std::shared_ptr<GameObject>>::iterator it = m_globalGameObjects.begin(); it != m_globalGameObjects.end(); ++it)
	{
		it->second->onComponentsUpdate(ticks);
		it->second->onUpdate(ticks);
	}

	m_game->onUpdate(ticks);


}

void GameManager::onEnd()
{
	m_game->onEnd();
	m_breakLoop = true;
}

void GameManager::fpsThrottle(int ticks)
{
	int delay = FRAME_RATE - ticks;
	if (delay > 0)
		SDL_Delay(delay);
}

void GameManager::addGameObject(int id, GameObject* obj)
{
	m_globalGameObjects[id] = std::shared_ptr<GameObject>(obj);
}

void GameManager::removeGameObject(GameObject* objectToRemove)
{
	m_gameObjectsToRemove.push_back(objectToRemove);
}

void GameManager::clearObjectsToRemove()
{
	//Do it by ID, don't kill the same ID twice
	sort(m_gameObjectsToRemove.begin(), m_gameObjectsToRemove.end());
	m_gameObjectsToRemove.erase(unique(m_gameObjectsToRemove.begin(), m_gameObjectsToRemove.end()), m_gameObjectsToRemove.end());

	for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
	{
		GameObject* object = m_gameObjectsToRemove[i];
		if (object == NULL)
			continue;
		m_globalGameObjects.erase(object->getId());
		SceneManager::getInstance()->getCurrentScene()->removeGameObject(object->getId());
		delete(object);
	}
	m_gameObjectsToRemove.clear();
}