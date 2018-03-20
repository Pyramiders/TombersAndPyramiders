#include "NetworkCharacter.h"
#include "CharacterController.h"
#include "Inventory.h"
#include "Receiver.h"
#include "Sender.h"

NetworkCharacter::NetworkCharacter(BasePilot* basePilot, int networkingID) :
	Character(basePilot)
{
	setFPS(12);
	addComponent<Inventory>(this);
	std::shared_ptr<Receiver> receiver = addComponent<Receiver> (this, networkingID);
	receiver->Subscribe ("ATTACK", [](std::map<std::string, void*> data) -> void
	{
		((NetworkCharacter*)data["this"])->getComponent<CharacterController> ()->useWeapon ();
	}, this);

	receiver->Subscribe ("TRIGGER", [](std::map<std::string, void*> data) -> void
	{
		if (!((NetworkCharacter*)data["this"])->getComponent<CharacterController> ()->tryInvokeTrigger ())
		{
			std::cout << "Sync Error on character receiving Trigger event. Should only be called on successful triggering, however receiver could not invoke a trigger." << std::endl;
		}
	}, this);
}

/*----------------------------------------------------------------------------------------
Instance Getter Methods
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
Instance Setter Methods
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
Instance Methods
----------------------------------------------------------------------------------------*/
void NetworkCharacter::onUpdate(int ticks)
{
	updateFrames(ticks);
}

void NetworkCharacter::onNetworkEnd () {
	destroy (getId ());
}
