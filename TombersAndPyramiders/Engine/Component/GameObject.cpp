#include "GameObject.h"
#include "Transform.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "GameManager.h"

GameObject::GameObject(bool g)
{
	m_id = rand() + rand();
	m_isGlobal = g;
	if (m_isGlobal)
		GameManager::getInstance()->addGameObject(m_id, this);
	if (SceneManager::getInstance()->hasScene())
		SceneManager::getInstance()->getCurrentScene()->addGameObject(m_id, this);
	m_transform = new Transform(this);
	addComponent<Transform*>(m_transform);
}

void GameObject::onComponentsUpdate(int ticks)
{
	for (std::map<std::string, std::vector<Component*>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			it->second[i]->onUpdate(ticks);
		}
	}
}

GameObject::~GameObject()
{
	removeAllComponents();
}

Transform* GameObject::getTransform()
{
	return m_transform;
}


void GameObject::destroy(GameObject* gameObject)
{
	GameManager::getInstance()->removeGameObject(gameObject);
}