#include "Receiver.h"

Receiver::Receiver(GameObject* gameObject, std::string netID) : Component(gameObject)
{
	this->netID = netID;
	//Add to map of type "event", key "id"

	this->m_onUpdateID = Subscribe("UPDATE", [](std::map<std::string, void*> data) -> void
	{
		float x = std::stof(*(std::string*)data["x"]);
		float y = std::stof(*(std::string*)data["y"]);
		float z = std::stof(*(std::string*)data["z"]);
		float angle = std::stof(*(std::string*)data["rotation"]);
		float scale = std::stof(*(std::string*)data["scale"]);

		Receiver* self = (Receiver*)data["this"];
		Transform* transform = self->gameObject->getTransform();
		transform->setPosition(x, y, z);
		transform->setRotation(angle);
		transform->setScale(scale);
	}, this);

	/*this->DestroySnowballID = Subscribe("DESTROYSNOWBALL", [](std::map<std::string, void*> data) -> void
	{
		Receiver* self = (Receiver*)data["this"];
		Snowball* snow = (Snowball *)self->gameObject;
		snow->DestructSnowball();
	}, this);

	this->DestroyBattlerID = Subscribe("DESTROYBATTLER", [](std::map<std::string, void*> data) -> void
	{
		Receiver* self = (Receiver*)data["this"];
		Battler* battler = (Battler *)self->gameObject;
		battler->Die();
	}, this);*/
}

Receiver::~Receiver()
{
	MessageManager::unSubscribe(netID + "|UPDATE", this->m_onUpdateID);
	/*MessageManager::UnSubscribe(netID + "|DESTROYSNOWBALL", this->DestroySnowballID);
	MessageManager::UnSubscribe(netID + "|DESTROYBATTLER", this->DestroyBattlerID);*/
}

int Receiver::Subscribe(std::string event, Callback callback, void* owner)
{
	return MessageManager::subscribe(netID + "|" + event, callback, owner);
}