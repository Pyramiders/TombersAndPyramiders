#include "Receiver.h"
#include "HostCharacter.h"
#include "NetworkingManager.h"
#include "CharacterController.h"
#include "Sender.h"
#include "HostPilot.h"

Receiver::Receiver(GameObject* gameObject, int netID) : Component(gameObject)
{
	this->netID = netID;
	//Add to map of type "event", key "id"
	this->m_onUpdateID = Subscribe("CREATE", [](std::map<std::string, void*> data) -> void
	{
		float netID = std::stoi (*(std::string*)data["netID"]);
		if (NetworkingManager::getInstance ()->isSelf (netID))
			return;
		float type = std::stof(*(std::string*)data["type"]);
		float x = std::stof(*(std::string*)data["x"]);
		float y = std::stof(*(std::string*)data["y"]);
		float z = std::stof(*(std::string*)data["z"]);
		float angle = std::stof(*(std::string*)data["rotation"]);
		float scale = std::stof(*(std::string*)data["scale"]);
		std::cout << "RECEIVED MESSAGE CREATE";
		Receiver* self = (Receiver*)data["this"];
		Transform* transform = self->gameObject->getTransform();
		transform->setPosition(x, y, z);
		transform->setRotation(angle);
		transform->setScale(scale);
	}, this);

	Subscribe ("SWAPPEDITEM", [](std::map<std::string, void*> data) -> void
	{
		Receiver* self = (Receiver*)data["this"];
		self->getGameObject ()->getComponent<CharacterController> ()->trySwapItem ();
	}, this);

	Subscribe ("HURT", [](std::map<std::string, void*> data) -> void
	{
		Receiver* self = (Receiver*)data["this"];
		float newHP = std::stoi (*(std::string*)data["newHealth"]);
		std::shared_ptr<CharacterController> cc = self->gameObject->getComponent<CharacterController> ();
		cc->setHealth (newHP);
	}, this);

	Subscribe ("TRYSWAPITEM", [](std::map<std::string, void*> data) -> void {
		float netID = std::stoi (*(std::string*)data["netID"]);
		if (NetworkingManager::getInstance ()->isSelf (netID))
			return;
		Receiver* self = (Receiver*)data["this"];
		if (self->getGameObject ()->getComponent<CharacterController> ()->trySwapItem () != nullptr) {
			std::shared_ptr<Sender> sender = self->getGameObject ()->getComponent<Sender> ();
			if (sender != nullptr) {
				sender->sendSwappedItem ();
			}
		}
	}, this);

	Subscribe ("ANIMATE", [](std::map<std::string, void*> data) -> void {
		Receiver* self = (Receiver*)data["this"];
		int animID = std::stoi (*(std::string*)data["animID"]);
		int animReturn = std::stoi (*(std::string*)data["animReturn"]);
		if (animReturn != -1) {
			((HostCharacter*)self->getGameObject ())->playAnimation (animID, animReturn);
		}
		else {
			((HostCharacter*)self->getGameObject ())->playAnimation (animID);
		}
	}, this);

	this->m_onUpdateID = Subscribe("DESTROY", [](std::map<std::string, void*> data) -> void
	{
		int id = std::stoi(*(std::string*)data["ID"]);
		Receiver* self = (Receiver*)data["this"];
		((Character*)self->gameObject)->onNetworkEnd ();
	}, this);

	this->m_onUpdateID = Subscribe("UPDATE", [](std::map<std::string, void*> data) -> void
	{
		float netID = std::stoi (*(std::string*)data["netID"]);
		if (NetworkingManager::getInstance ()->isSelf (netID))
			return;
		float x = std::stof(*(std::string*)data["x"]);
		float y = std::stof(*(std::string*)data["y"]);
		float z = std::stof (*(std::string*)data["z"]);
		float vecX = std::stof (*(std::string*)data["vecX"]);
		float vecY = std::stof (*(std::string*)data["vecY"]);
		float angle = std::stof(*(std::string*)data["rotation"]);
		float scale = std::stof(*(std::string*)data["scale"]);
		Receiver* self = (Receiver*)data["this"];
		Transform* transform = self->gameObject->getTransform();
		transform->setPosition(x, y, z);
		transform->setRotation(angle);
		transform->setScale(scale);


		std::shared_ptr<CharacterController> cc = self->gameObject->getComponent<CharacterController> ();
		((HostPilot*)cc->getPilot ())->setMovement(Vector2 (vecX, vecY), 6);
	}, this);
}

Receiver::~Receiver()
{
	MessageManager::unSubscribe(std::to_string (netID) + "|UPDATE", this->m_onUpdateID);
}

int Receiver::Subscribe(std::string event, Callback callback, void* owner)
{
	return MessageManager::subscribe(std::to_string(netID) + "|" + event, callback, owner);
}
