#include "HostPilot.h"
#include "CharacterController.h"
#include "InputManager.h"
#include "Vector2.h"

void HostPilot::setController(BaseController* controller)
{
	m_lastNetworkVector = Vector2 (0, 0);
	BasePilot::setController(controller);

	/* Store a correctly typed pointer to the controller for convenience. */
	m_characterController = static_cast<CharacterController*>(controller);
}

/*----------------------------------------------------------------------------------------
Instance Methods
----------------------------------------------------------------------------------------*/
void HostPilot::onStart()
{}

void HostPilot::onUpdate(int ticks)
{
	
	if (m_characterController != nullptr && updatesSinceNewMovement < updatesUntilInvalid)
	{
		m_characterController->move(getMovement());
		updatesSinceNewMovement++;
	}
	/*
	if (getWeaponInput())
	{
		m_characterController->useWeapon();
	}
	*/
}

void HostPilot::onEnd()
{}

void HostPilot::setMovement (Vector2 vec, int updates) {
	m_lastNetworkVector = vec;
	updatesUntilInvalid = updates;
	updatesSinceNewMovement = 0;
}

Vector2 HostPilot::getMovement()
{
	return m_lastNetworkVector;
}

bool HostPilot::getWeaponInput()
{
	return false;
}
