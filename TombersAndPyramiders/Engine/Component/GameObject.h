#pragma once

#include "Component.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <map>
#include "Updateable.h"
#include "Transform.h"
#include <iostream>

class GameObject : public Updateable
{
private:
	std::map<std::string, std::vector<Component*>> m_components;
	int m_id;
	bool m_isGlobal;
	Transform* m_transform;

	template <typename T>
	std::string getClassName()
	{
		return typeid(T).name();
	}

public:
	GameObject(bool isGlobal);

	int getId()
	{
		return m_id;
	}

	template <typename T>
	T getComponent()
	{
		if (hasComponent<T>())
		{
			return (T)m_components[getClassName<T>()].front();
		}
		else
		{
			std::cout << "ERROR::FAILED TO FIND COMPONENT " << getClassName<T>() << "  FOR OBJECT " << m_id << std::endl;
			return NULL;
		}
	}

	template <typename T>
	std::vector<T> getComponents()
	{
		return (T)m_components[getClassName<T>()];
	}

	template <typename T>
	void addComponent(T component)
	{
		std::string id = getClassName<T>();
		if (!hasComponent<T>())
		{
			std::vector<Component*> typeList;
			typeList.push_back((Component*)component);
			m_components.insert(std::pair<std::string, std::vector<Component*>>(id, typeList));
		}
		else
		{
			m_components[id].push_back(component);
		}
	}

	template <typename T>
	void removeComponents()
	{
		std::vector<Component*> componentList = m_components[getClassName<T>()];
		for (size_t i = componentList.size() - 1; i >= 0; i--)
		{
			delete componentList[i];
		}

		m_components[getClassName<T>()].clear();
	}

	void removeAllComponents()
	{
		for (std::map<std::string, std::vector<Component*>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			for (size_t i = 0; i < it->second.size(); i++)
			{
				it->second[i]->~Component();
				delete it->second[i];
				it->second[i] = NULL;
			}
		}
		m_components.clear();
	}

	template <typename T>
	bool hasComponent()
	{
		return m_components.find(getClassName<T>()) != m_components.end();
	}

	void onStart() {};
	void onComponentsUpdate(int ticks);
	void onUpdate(int ticks) {};
	void onEnd() {};
	Transform* getTransform();

	void destroy(GameObject* gameObject);

	virtual ~GameObject();
};