
#include "SceneManager.h"
#include <iostream>
#include "Scene.h"

SceneManager* SceneManager::s_instance;

SceneManager* SceneManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new SceneManager();
	return s_instance;
}

SceneManager::SceneManager()
{
}

void SceneManager::pushScene(Scene *scene)
{
	if (!m_scenes.empty())
	{
		m_scenes.top()->onPause();
	}
	m_scenes.push(scene);
	scene->onStart();
}

bool SceneManager::updateScene(int ticks)
{
	if (m_scenes.empty())
		return false;
	m_scenes.top()->onObjectsUpdate(ticks);
	m_scenes.top()->onUpdate(ticks);
	return true;
}

bool SceneManager::hasScene()
{
	return !m_scenes.empty();
}

bool SceneManager::popScene()
{
	if (m_scenes.empty())
		return false;
	m_scenes.top()->onEnd();
	m_scenes.pop();
	m_scenes.top()->onResume();
	return true;
}

Scene* SceneManager::getCurrentScene()
{
	if (m_scenes.empty())
		return NULL;
	return m_scenes.top();
}