#include "MessageManager.h"

MessageManager* MessageManager::s_instance;

MessageManager* MessageManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new MessageManager();
	return s_instance;
}

int MessageManager::subscribe(std::string event, Callback callback, void* owner)
{
	MessageManager* self = MessageManager::getInstance();
	CallbackReceiver callbackReceiver;
	callbackReceiver.callback = callback;
	callbackReceiver.owner = owner;

	int id = rand();

	std::map<std::string, std::map<int, CallbackReceiver> >::iterator it = self->m_subs.find(event);
	if (it != self->m_subs.end())
		it->second[id] = callbackReceiver;
	else
	{
		std::map<int, CallbackReceiver> eventList;
		eventList[id] = callbackReceiver;
		self->m_subs[event] = eventList;
	}
	return id;
}

void MessageManager::unSubscribe(std::string event, int id)
{
	MessageManager* self = MessageManager::getInstance();

	std::map<std::string, std::map<int, CallbackReceiver> >::iterator it = self->m_subs.find(event);
	if (it != self->m_subs.end())
		it->second.erase(id);
}

void MessageManager::sendEvent(std::string event, std::map<std::string, void*> data)
{
	MessageManager* self = MessageManager::getInstance();

	std::map<std::string, std::map<int, CallbackReceiver> >::iterator it = self->m_subs.find(event);
	if (it != self->m_subs.end())
		for (std::map<int, CallbackReceiver>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			data["this"] = (void*)it2->second.owner;
			it2->second.callback(data);
		}
	//TODO: Clear all void* data that isn't "this"
}