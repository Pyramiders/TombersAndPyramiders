#include "HostCharacter.h"
#include "CharacterController.h"
#include "Inventory.h"
#include "Receiver.h"
#include "Sender.h"
#include "SpawnManager.h"

HostCharacter::HostCharacter(BasePilot* basePilot, int networkingID) :
	Character(basePilot)
{
	std::shared_ptr<Receiver> receiver = addComponent<Receiver> (this, networkingID);
	std::shared_ptr<Sender> sender = addComponent<Sender> (this, networkingID);
	receiver->Subscribe("ATTACK", [](std::map<std::string, void*> data) -> void 
	{
		((HostCharacter*)data["this"])->getComponent<CharacterController>()->useWeapon();
	}, this);

	receiver->Subscribe("TRIGGER", [](std::map<std::string, void*> data) -> void
	{
		if (!((HostCharacter*)data["this"])->getComponent<CharacterController>()->tryInvokeTrigger())
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
void HostCharacter::onUpdate(int ticks)
{
	updateFrames(ticks);
}

void HostCharacter::onNetworkEnd () {
	auto receiver = getComponent<Receiver>();
	if (receiver != nullptr) {
		SpawnManager::getInstance()->generateNetworkGhost(getTransform()->getX(), getTransform()->getY(), receiver->netID, false);
	}
	destroy (getId ());
}

bool HostCharacter::playRunAnimation () {
	if (Character::playRunAnimation ())
	{
		getComponent<Sender> ()->sendAnimation (ANIMATION_WALK);
		return true;
	}
	return false;
}
bool HostCharacter::endRunAnimation () {
	if (Character::endRunAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_IDLE);
		return true;
	}
	return false;
}

bool HostCharacter::playMeleeAttackAnimation () {
	if (Character::playMeleeAttackAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_ATTACK_MELEE, ANIMATION_IDLE);
		return true;
	}
	return false;
}

bool HostCharacter::playRangeAttackAnimation () {
	if (Character::playRangeAttackAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_ATTACK_RANGE, ANIMATION_IDLE);
		return true;
	}
	return false;
}

bool HostCharacter::playHurtAnimation () {
	if (Character::playHurtAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_HURT, ANIMATION_IDLE);
		return true;
	}
	return false;
}