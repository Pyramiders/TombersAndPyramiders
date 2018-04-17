#include "GhostReceiverPilot.h"
#include "GhostController.h"
#include "Receiver.h"
#include "GhostCharacter.h"

GhostReceiverPilot::GhostReceiverPilot()
{
	m_lastNetworkVector = Vector2(0, 0);
	m_hasInit = false;
	
}

//On loading in a controller, if it's our first time loading the m_ghostController, set it
void GhostReceiverPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);
	if (m_ghostController == nullptr)
	{
		m_possessableController = nullptr;
		m_ghostController = m_controller;
	}
}

void GhostReceiverPilot::onStart()
{
	if (!m_hasInit) 
	{
		auto receiver = m_controller->getGameObject()->getComponent<Receiver>();
		if (receiver != nullptr) 
		{
			receiver->Subscribe("GHOSTTRIGGER", [](std::map<std::string, void*> data) -> void
			{
				GhostReceiverPilot* self = (GhostReceiverPilot*)data["this"];
				self->tryTrigger();

			}, this);
			receiver->Subscribe("GHOSTPOSSESS", [](std::map<std::string, void*> data) -> void
			{
				std::shared_ptr<BasePossessableController> closest;
				GhostReceiverPilot* self = (GhostReceiverPilot*)data["this"];
				auto ghostController = dynamic_cast<GhostController*>(self->getController());
				if (ghostController->tryPossessClosest(closest)) //Try and possess, make sure its close enough
				{
					self->setPossession(closest); //If our controller successfully possessed it, update our Pilot to know so
				} else {
					std::cout << "Sync Error on character receiving Trigger event. Should only be called on successful triggering, however receiver could not invoke a trigger." << std::endl;
				}
			}, this);
			receiver->Subscribe("GHOSTUNPOSSESS", [](std::map<std::string, void*> data) -> void
			{
				GhostReceiverPilot* self = (GhostReceiverPilot*)data["this"];
				self->setPossession(nullptr);
			}, this);
			receiver->Subscribe("GHOSTMOVEPOSSESSION", [](std::map<std::string, void*> data) -> void
			{
				GhostReceiverPilot* self = (GhostReceiverPilot*)data["this"];
				Vector2 movement = Vector2(std::stof(*(std::string*)data["xVel"]), std::stof(*(std::string*)data["yVel"]));
				self->movePossessable(movement);
			}, this);
		}

		m_hasInit = true;
	}
}

void GhostReceiverPilot::movePossessable(Vector2 movement)
{
	if (m_possessableController != nullptr)
	{
		m_possessableController->move(movement);
	}
}

void GhostReceiverPilot::tryTrigger() 
{
	if (m_possessableController != nullptr)
	{
		m_possessableController->trigger();
	}
}

void GhostReceiverPilot::setPossession(std::shared_ptr<BasePossessableController> possession)
{
	if (possession != nullptr) 
	{
		// If we are trying to possess something, possess it
		m_controller->swapPilots(dynamic_cast<BaseController*>(possession.get()));
		m_possessableController = possession;
		m_possessableController->onPossessionStart();
	}
	else 
	{
		// If we are trying to stop possessing, stop possessing
		GhostController* ghostControllerRaw = dynamic_cast<GhostController*>(m_ghostController);
		Transform* possessTrans = m_possessableController->getGameObject()->getTransform();
		m_ghostController->getGameObject()->getTransform()->setPosition(possessTrans->getX(), possessTrans->getY());
		m_possessableController->swapPilots(m_ghostController);
		m_possessableController->onPossessionEnd();
		m_possessableController = nullptr;
		m_ghostController->getGameObject()->getTransform()->setScale(1.0f);
		auto ghostController = dynamic_cast<GhostController*>(m_ghostController);
		if (ghostController != nullptr) 
		{
			ghostController->stopPossessing();
		}
		else {
			std::cout << "Attached controller was not a GhostController" << std::endl;
		}
	}
}

void GhostReceiverPilot::onUpdate(int ticks)
{
	if (!m_hasInit) {
		onStart();
	}
	GhostController* ghostControllerRaw = dynamic_cast<GhostController*>(m_controller);
	if (ghostControllerRaw != nullptr && m_updatesSinceNewMovement < m_updatesUntilInvalid)
	{
		ghostControllerRaw->move(*(m_lastNetworkVector * ((float)ticks / 1000.0f)));
		m_updatesSinceNewMovement++;
	}
}

void GhostReceiverPilot::onEnd()
{

}

void GhostReceiverPilot::setMovement(Vector2 vec, int updates) {
	m_lastNetworkVector.setX(vec.getX());
	m_lastNetworkVector.setY(vec.getY());
	m_updatesUntilInvalid = updates;
	m_updatesSinceNewMovement = 0;
}