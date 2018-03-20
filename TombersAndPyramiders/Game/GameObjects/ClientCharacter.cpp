#include "ClientCharacter.h"
#include "CharacterController.h"
#include "Inventory.h"
#include "Sender.h"
#include "MessageManager.h"

ClientCharacter::ClientCharacter(BasePilot* basePilot, int networkingID) :
	Character(basePilot)
{
	addComponent<Sender>(this, networkingID);
	MessageManager::subscribe (std::to_string (networkingID) + "|" + "SWAPPEDITEM", [](std::map<std::string, void*> data) -> void
	{
		ClientCharacter* self = (ClientCharacter*)data["this"];
		self->getComponent<CharacterController> ()->trySwapItem ();
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
void ClientCharacter::onUpdate(int ticks)
{
	updateFrames(ticks);
}

void ClientCharacter::onEnd () {
	getComponent<Sender> ()->sendDestroy ();
	destroy (getId ());
}

bool ClientCharacter::playRunAnimation () {
	if (Character::playRunAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_RUN);
		return true;
	}
	return false;
}
bool ClientCharacter::endRunAnimation () {
	if (Character::endRunAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_IDLE);
		return true;
	}
	return false;
}

bool ClientCharacter::playMeleeAttackAnimation () {
	if (Character::playMeleeAttackAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_ATTACK_MELEE, ANIMATION_IDLE);
		return true;
	}
	return false;
}

bool ClientCharacter::playRangeAttackAnimation () {
	if (Character::playRangeAttackAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_ATTACK_RANGE, ANIMATION_IDLE);
		return true;
	}
	return false;
}

bool ClientCharacter::playHurtAnimation () {
	if (Character::playHurtAnimation ()) {
		getComponent<Sender> ()->sendAnimation (ANIMATION_HURT, ANIMATION_IDLE);
		return true;
	}
	return false;
}