/*===================================================================================*//**
	Character
	
	Prefab class for any character.
    
    Copyright 2017 Erick Fernandez de Arteaga. All rights reserved.
        https://www.linkedin.com/in/erick-fda
        https://bitbucket.org/erick-fda
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Character.h"
#include "CharacterController.h"
#include "Inventory.h"
#include "Sender.h"
#include "Receiver.h"
#include "SpawnManager.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
Character::Character(BasePilot* basePilot, CharacterType type) :
	ComplexSprite(generateComplexSpriteInfo(type), 0, 0)
{
	setFPS(12);
	Inventory* inventory = addComponent<Inventory>(this).get();
	addComponent<CharacterController>(this, inventory, basePilot);

	switch (type)
	{
	case player:
		m_walk = "male_walk";
		m_shoot = "male_bow";
		m_slash = "male_melee_slash";
		break;
	case beetle:
		m_walk = "beetle_walk";
		m_shoot = "beetle_shoot";
		m_slash = "beetle_slash";
		break;
	}

	currentState = IDLE_UP;
	changeSpriteSheet(m_walk);
	changeAnimation(m_idleUp);
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
void Character::onUpdate(int ticks)
{
	updateFrames(ticks);
}

// Private generation logic for describing the sprite sheet relationships for this player
std::shared_ptr<ComplexSpriteInfo> Character::generateComplexSpriteInfo(CharacterType type)
{
	std::shared_ptr<ComplexSpriteInfo> spriteInfo = std::make_shared<ComplexSpriteInfo>();

	std::string walk = std::string("");
	std::string shoot = std::string("");
	std::string slash = std::string("");
	switch (type)
	{
	case player:
		spriteInfo->addSprite("Player/Walk/male_walk.png", "male_walk", 9, 4);
		spriteInfo->addSprite("Player/Attack/Melee/male_melee_slash.png", "male_melee_slash", 6, 4);
		spriteInfo->addSprite("Player/Attack/Bow/male_bow.png", "male_bow", 13, 4);

		walk = std::string("male_walk");
		shoot = std::string("male_bow");
		slash = std::string("male_melee_slash");

		spriteInfo->addAnimation(walk, "WalkUp", 1, 8);
		spriteInfo->addAnimation(walk, "WalkLeft", 10, 17);
		spriteInfo->addAnimation(walk, "WalkDown", 19, 26);
		spriteInfo->addAnimation(walk, "WalkRight", 28, 35);
		spriteInfo->addAnimation(walk, "IdleUp", 0, 0);
		spriteInfo->addAnimation(walk, "IdleLeft", 9, 9);
		spriteInfo->addAnimation(walk, "IdleDown", 18, 18);
		spriteInfo->addAnimation(walk, "IdleRight", 27, 27);

		spriteInfo->addAnimation(slash, "SlashUp", 1, 5);
		spriteInfo->addAnimation(slash, "SlashLeft", 7, 11);
		spriteInfo->addAnimation(slash, "SlashDown", 13, 17);
		spriteInfo->addAnimation(slash, "SlashRight", 19, 23);
		spriteInfo->addAnimation(slash, "IdleUp", 0, 0);
		spriteInfo->addAnimation(slash, "IdleLeft", 6, 6);
		spriteInfo->addAnimation(slash, "IdleDown", 12, 12);
		spriteInfo->addAnimation(slash, "IdleRight", 18, 18);

		spriteInfo->addAnimation(shoot, "ShootUp", 1, 12);
		spriteInfo->addAnimation(shoot, "ShootLeft", 14, 25);
		spriteInfo->addAnimation(shoot, "ShootDown", 27, 38);
		spriteInfo->addAnimation(shoot, "ShootRight", 40, 51);
		spriteInfo->addAnimation(shoot, "IdleUp", 0, 0);
		spriteInfo->addAnimation(shoot, "IdleLeft", 13, 13);
		spriteInfo->addAnimation(shoot, "IdleDown", 26, 26);
		spriteInfo->addAnimation(shoot, "IdleRight", 39, 39);
		break;
	case beetle:
		spriteInfo->addSprite("Enemies/beetle_walk.png", "beetle_walk", 3, 4);
		spriteInfo->addSprite("Enemies/beetle_walk.png", "beetle_shoot", 3, 4);
		spriteInfo->addSprite("Enemies/beetle_walk.png", "beetle_slash", 3, 4);

		walk = "beetle_walk";
		shoot = "beetle_shoot";
		slash = "beetle_slash";

		spriteInfo->addAnimation(walk, "WalkUp", 0, 2);
		spriteInfo->addAnimation(walk, "WalkLeft", 3, 5);
		spriteInfo->addAnimation(walk, "WalkDown", 6, 8);
		spriteInfo->addAnimation(walk, "WalkRight", 9, 11);
		spriteInfo->addAnimation(walk, "IdleUp", 1, 1);
		spriteInfo->addAnimation(walk, "IdleLeft", 4, 4);
		spriteInfo->addAnimation(walk, "IdleDown", 7, 7);
		spriteInfo->addAnimation(walk, "IdleRight", 10, 10);

		spriteInfo->addAnimation(slash, "SlashUp", 1, 1);
		spriteInfo->addAnimation(slash, "SlashLeft", 4, 4);
		spriteInfo->addAnimation(slash, "SlashDown", 7, 7);
		spriteInfo->addAnimation(slash, "SlashRight", 10, 10);
		spriteInfo->addAnimation(slash, "IdleUp", 1, 1);
		spriteInfo->addAnimation(slash, "IdleLeft", 4, 4);
		spriteInfo->addAnimation(slash, "IdleDown", 7, 7);
		spriteInfo->addAnimation(slash, "IdleRight", 10, 10);

		spriteInfo->addAnimation(shoot, "ShootUp", 1, 1);
		spriteInfo->addAnimation(shoot, "ShootLeft", 4, 4);
		spriteInfo->addAnimation(shoot, "ShootDown", 7, 7);
		spriteInfo->addAnimation(shoot, "ShootRight", 10, 10);
		spriteInfo->addAnimation(shoot, "IdleUp", 1, 1);
		spriteInfo->addAnimation(shoot, "IdleLeft", 4, 4);
		spriteInfo->addAnimation(shoot, "IdleDown", 7, 7);
		spriteInfo->addAnimation(shoot, "IdleRight", 10, 10);

		break;
	}
	
	return spriteInfo;
}

// Changes the sprite to the specified ID
bool Character::playAnimation(int animID, int animReturn)
{
	if (animReturn != -1) 
	{
		if (animID == ANIMATION_ATTACK_MELEE)
		{
			playMeleeAttackAnimation();
		}
		else if (animID == ANIMATION_ATTACK_RANGE)
		{
			playRangeAttackAnimation();
		}
		else if (animID == ANIMATION_HURT)
		{
			playHurtAnimation();
		}
		else
		{
			return false;
		}
	}
	else 
	{
		if (animID == ANIMATION_WALK)
		{
			playRunAnimation();
		}
		else
		{
			endRunAnimation();
		}
	}
	return true;
}

// Changes the sprite animation to running
bool Character::playRunAnimation()
{
	float rotation = getTransform()->getRotation();

	if (rotation < 90)
	{
		changeSpriteSheet(m_walk);
		changeAnimation(m_walkRight);
		currentState = WALK_RIGHT;
		return true;
	}
	else if (rotation < 180)
	{
		changeSpriteSheet(m_walk);
		changeAnimation(m_walkDown);
		currentState = WALK_DOWN;
		return true;
	}
	else if (rotation < 270)
	{
		changeSpriteSheet(m_walk);
		changeAnimation(m_walkLeft);
		currentState = WALK_LEFT;
		return true;
	}
	else if (rotation >= 270 && rotation <= 360)
	{
		changeSpriteSheet(m_walk);
		changeAnimation(m_walkUp);
		currentState = WALK_UP;
		return true;
	}

	return false;
}


// Changes the sprite animation to idling
bool Character::endRunAnimation()
{
	switch (currentState)
	{
		case WALK_UP:
			changeSpriteSheet(m_walk);
			changeAnimation(m_idleUp);
			currentState = IDLE_UP;
			return true;
		case WALK_RIGHT:
			changeSpriteSheet(m_walk);
			changeAnimation(m_idleRight); 
			currentState = IDLE_RIGHT;
			return true;
		case WALK_DOWN:
			changeSpriteSheet(m_walk);
			changeAnimation(m_idleDown); 
			currentState = IDLE_DOWN;
			return true;
		case WALK_LEFT:
			changeSpriteSheet(m_walk);
			changeAnimation(m_idleLeft); 
			currentState = IDLE_LEFT;
			return true;
	}
	return false;
}


// Changes the sprite animation to the melee attack for one animation then returns back to idle
bool Character::playMeleeAttackAnimation()
{
	float rotation = getTransform()->getRotation();
	if (rotation < 90)
	{
		changeSpriteSheet(m_slash);
		changeAnimation(m_slashRight, m_idleRight);
		currentState = IDLE_RIGHT;
	}
	else if (rotation < 180)
	{
		changeSpriteSheet(m_slash);
		changeAnimation(m_slashDown, m_idleDown);
		currentState = IDLE_DOWN;
	}
	else if (rotation < 270)
	{
		changeSpriteSheet(m_slash);
		changeAnimation(m_slashLeft, m_idleLeft);
		currentState = IDLE_LEFT;
	}
	else
	{
		changeSpriteSheet(m_slash);
		changeAnimation(m_slashUp, m_idleUp);
		currentState = IDLE_UP;
	}
	return true;
}

// Changes the sprite animation to the range attack for one animation then returns back to idle
bool Character::playRangeAttackAnimation()
{
	float rotation = getTransform()->getRotation();
	if (rotation < 90)
	{
		changeSpriteSheet(m_shoot);
		changeAnimation(m_shootRight, m_idleRight);
		currentState = IDLE_RIGHT;
	}
	else if (rotation < 180)
	{
		changeSpriteSheet(m_shoot);
		changeAnimation(m_shootDown, m_idleDown);
		currentState = IDLE_DOWN;
	}
	else if (rotation < 270)
	{
		changeSpriteSheet(m_shoot);
		changeAnimation(m_shootLeft, m_idleLeft);
		currentState = IDLE_LEFT;
	}
	else
	{
		changeSpriteSheet(m_shoot);
		changeAnimation(m_shootUp, m_idleUp);
		currentState = IDLE_UP;
	}

	return true;
}

bool Character::playHurtAnimation()
{
	//float rotation = getTransform()->getRotation();
	//if (rotation < 90)
	//{
	//	changeSpriteSheet(ANIMATION_HURT_RIGHT, ANIMATION_IDLE_RIGHT);
	//}
	//else if (rotation < 180)
	//{
	//	changeSpriteSheet(ANIMATION_HURT_DOWN, ANIMATION_IDLE_DOWN);
	//}
	//else if (rotation < 270)
	//{
	//	changeSpriteSheet(ANIMATION_HURT_LEFT, ANIMATION_IDLE_LEFT);
	//}
	//else
	//{
	//	changeSpriteSheet(ANIMATION_HURT_UP, ANIMATION_IDLE_UP);
	//}

	return true;
}

void Character::onNetworkEnd() {
	auto sender = getComponent<Sender> ();
	if (sender != nullptr) {
		sender->sendDestroy ();
	}
	destroy (getId ());
}