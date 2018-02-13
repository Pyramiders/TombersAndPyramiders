#pragma once

#include <string>
#include "GameObject.h"
#include "Transform.h"
#include <iostream>

//Senders transform message and extra commands

class Sender : public Component
{
private:
	std::string m_id;

public:
	Sender(GameObject* gameObject, std::string ID);
	void sendUpdate();
	void sendNetworkMessage(std::string messageKey, std::map<std::string, std::string> payload);
	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};
	~Sender();
};