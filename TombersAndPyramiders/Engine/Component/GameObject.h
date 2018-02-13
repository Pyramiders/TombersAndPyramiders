#pragma once

#include "Component.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <map>
#include "Updateable.h"
#include "Transform.h"
#include <iostream>
#include <memory>


template<int> //template parameter could be anything!
void dynamic_pointer_cast(); //ADD this. NO NEED TO DEFINE IT

class GameObject : public Updateable
{
private:
	std::map<std::string, std::vector<std::shared_ptr<Component>>> m_components;
	int m_id = 0;
	bool m_isGlobal;
	std::shared_ptr<Transform> m_transform;

	template <typename T>
	std::string getClassName()
	{
		return typeid(T).name();
	}

public:
	GameObject();

	int getId()
	{
		return m_id;
	}
	void GameObject::setInitialState(bool isGlobal, int id);


	template <class T>
	std::shared_ptr<T> getComponent()
	{
		std::string componentName = getClassName<T>();
		if (hasComponent(componentName))
		{
			return dynamic_pointer_cast<T, Component>(m_components[componentName].front());
		}
		else
		{

			return nullptr;
		}
	}

	template <typename T>
	std::vector<T> getComponents()
	{
		return (T)m_components[getClassName<T>()];
	}
	template <typename T, class... _Types>
	std::shared_ptr<T> addComponent(_Types&&... args)
	{
		std::shared_ptr<T> component = std::make_shared<T>(args...);
		std::string id = getClassName<T>();
		if (!hasComponent<T>())
		{
			std::vector<std::shared_ptr<Component>> typeList;
			typeList.push_back(component);
			m_components.insert(std::pair<std::string, std::vector<std::shared_ptr<Component>>>(id, typeList));
		}
		else
		{
			m_components[id].push_back(component);
		}
		return component;
	}

	template <typename T>
	void removeComponents()
	{
		std::vector<std::shared_ptr<Component>> componentList = m_components[getClassName<T>()];
		for (size_t i = componentList.size() - 1; i >= 0; i--)
		{
			delete componentList[i];
		}

		m_components[getClassName<T>()].clear();
	}

	void removeAllComponents()
	{
		/*for (std::map<std::string, std::vector<Component*>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			for (size_t i = 0; i < it->second.size(); i++)
			{
				delete it->second[i];
				it->second[i] = NULL;
			}
		}*/
		m_components.clear();
	}

	template <typename T>
	bool hasComponent()
	{
		return m_components.find(getClassName<T>()) != m_components.end();
	}
	bool hasComponent(std::string componentName)
	{
		return m_components.find(componentName) != m_components.end();
	}

	void onStart() {};
	void onComponentsUpdate(int ticks);
	void onUpdate(int ticks) {};
	void onEnd() {};
	Transform* getTransform();

	void destroy(const std::shared_ptr<GameObject> gameObject);
	void destroy(int gameObjectId);

	virtual ~GameObject();
};