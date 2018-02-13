#include "Sender.h"
#include "NetworkingManager.h"

Sender::Sender(GameObject* gameObject, std::string ID) : Component(gameObject)
{
	this->m_id = ID;
}

void Sender::sendUpdate()
{
	std::map<std::string, std::string> payload;
	Transform* transform = gameObject->getTransform();
	payload["x"] = std::to_string(transform->getX());
	payload["y"] = std::to_string(transform->getY());
	payload["z"] = std::to_string(transform->getZ());
	payload["rotation"] = std::to_string(transform->getRotation());
	payload["scale"] = std::to_string(transform->getScale());
	sendNetworkMessage("UPDATE", payload);
}

void Sender::sendNetworkMessage(std::string messageKey, std::map<std::string, std::string> payload)
{
	std::remove_if(messageKey.begin(), messageKey.end(), isspace);
	NetworkingManager::getInstance()->prepareMessageForSending(this->m_id + "|" + messageKey, payload);
}

Sender::~Sender()
{
	std::map<std::string, std::string> payload;
}

void Sender::onUpdate(int ticks)
{
	sendUpdate();
}