#include "GameObject.h"
#include "Transform.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "GameManager.h"

GameObject::GameObject()
{
	m_transform = addComponent<Transform>(this);
}

void GameObject::onComponentsUpdate(int ticks)
{
	for (std::map<std::string, std::vector<std::shared_ptr<Component>>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			it->second[i]->onUpdate(ticks);
		}
	}
}

void GameObject::setInitialState(bool isGlobal, int id)
{
	if (m_id == 0)
	{
		m_id = id;
		m_isGlobal = isGlobal;
	}
	else
	{
		throw "ID already set for GameObject";
	}
}

GameObject::~GameObject()
{
	removeAllComponents();
}

Transform* GameObject::getTransform()
{
	return m_transform.get();
}

void GameObject::destroy(const std::shared_ptr<GameObject> gameObject)
{
	destroy(gameObject->getId());
}

void GameObject::destroy(int gameObjectid)
{
	GameManager::getInstance()->removeGameObject(gameObjectid);
}