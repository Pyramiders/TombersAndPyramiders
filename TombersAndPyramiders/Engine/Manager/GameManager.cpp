#include "GameManager.h"
#include "InputManager.h"
#include "SpriteRendererManager.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "MessageManager.h"
#include "NetworkingManager.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include <memory>
#include "Camera.h"
#include "SharedConstants.h"

GameManager* GameManager::s_instance;

GameManager* GameManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new GameManager();
	return s_instance;
}

GameManager::GameManager()
{
	reinstantiateQuadTree(getGameWidth() / 2.0f, getGameHeight() / 2.0f, getGameWidth(), getGameHeight());
}

void GameManager::onStart()
{
	resizeQuadTree(12 * 5 / 2.0f, -12 * 5 / 2.0f, 12 * 5 * 1.25f, 12 * 5 * 1.25f);
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

	updateQuadTree();
	PhysicsManager::getInstance()->onUpdate(ticks);
	SpriteRendererManager::getInstance()->onUpdate(ticks);

	for (std::map<int, std::shared_ptr<GameObject>>::iterator it = m_globalGameObjects.begin(); it != m_globalGameObjects.end(); ++it)
	{
		if (it->second != nullptr) {
			it->second->onComponentsUpdate(ticks);
			it->second->onUpdate(ticks);
		}
	}

	m_game->onUpdate(ticks);


}

void GameManager::reinstantiateQuadTree(float x, float y, float width, float height)
{
	m_quadTree.reset(new QuadTree(QuadTreeBounds(x, y, width, height))); //Width/Height of playable world
}

void GameManager::resizeQuadTree(float x, float y, float width, float height) 
{
	std::set<std::shared_ptr<GameObject>> toMove = m_quadTree->getAll();
	reinstantiateQuadTree(x, y, width, height);
	for(auto it = toMove.begin(); it != toMove.end(); it++)
	{
		m_quadTree->insert(*it);
	}
}

void GameManager::updateQuadTree() {
	if (m_quadTree->reconstruct() > 50)
	{
 		resizeQuadTree(m_quadTree->getBounds().getX(), m_quadTree->getBounds().getY(),m_quadTree->getBounds().getWidth(), m_quadTree->getBounds().getHeight());
	}
}

std::vector<std::shared_ptr<GameObject>> GameManager::getObjectsInBounds(float x, float y, float width, float height)
{
	std::vector<std::shared_ptr<GameObject>> result;
	m_quadTree->populateList(QuadTreeBounds(x, y, width, height), result);
	//std::cout << x << " " << y << " | " << width << " " << height << " | " << result.size() << std::endl;
	result.erase(std::unique(result.begin(), result.end()), result.end());
	return result;
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

void GameManager::addGameObject(int id, std::shared_ptr<GameObject> obj)
{
	m_globalGameObjects[id] = obj;
}
//void GameObject::destroy(int gameObjectId)
void GameManager::removeGameObject(int objectToRemove)
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
		int id = m_gameObjectsToRemove[i];
		std::shared_ptr<GameObject> object = m_globalGameObjects[id];
		if (object == nullptr) 
		{
			object = SceneManager::getInstance()->getCurrentScene()->sceneObjects[id];
		}
		if (object != nullptr)
		{
			m_globalGameObjects.erase(id);
			SceneManager::getInstance()->getCurrentScene()->removeGameObject(id);
			std::shared_ptr<SpriteRenderer> renderer = object->getComponent<SpriteRenderer>();
			if (renderer != nullptr) 
			{
				SpriteRendererManager::getInstance()->removeSpriteFromRendering(id);
			}
			std::shared_ptr<BoxCollider> collider = object->getComponent<BoxCollider>();
			if (collider != nullptr)
			{
				PhysicsManager::getInstance()->removeCollider(collider.get());
			}
		}
	}
	m_gameObjectsToRemove.clear();
}