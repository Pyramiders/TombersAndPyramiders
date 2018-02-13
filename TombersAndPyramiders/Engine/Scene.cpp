#include "Scene.h"
#include "SpriteRenderer.h"
#include "Collision/Collider.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "GameObject.h"

void Scene::addGameObject(int id, std::shared_ptr<GameObject> obj)
{
	if (obj != nullptr)
	{
		sceneObjects[id] = obj;
	}
}

void Scene::removeGameObject(int id)
{
	m_idsToRemove.push_back(id);
}

void Scene::onObjectsUpdate(int ticks)
{
	for (int i = 0; i < m_idsToRemove.size(); i++)
	{
		sceneObjects.erase(m_idsToRemove[i]);
	}
	m_idsToRemove.clear();
	for (std::map<int, std::shared_ptr<GameObject>>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		if (it->second != nullptr && it->second != NULL)
		{
			it->second->onComponentsUpdate(ticks);
			it->second->onUpdate(ticks);
		}
		else
		{
			int hit = true;
		}
	}
}

void Scene::purge()
{
	sceneObjects.clear();
}