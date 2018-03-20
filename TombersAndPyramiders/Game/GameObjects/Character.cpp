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
#include "SpawnManager.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
Character::Character(BasePilot* basePilot) :
	ComplexSprite(generateComplexSpriteInfo(), 0, 0)
{
	setFPS(12);
	Inventory* inventory = addComponent<Inventory>(this).get();
	addComponent<CharacterController>(this, inventory, basePilot);
	//m_health = SpawnManager::getInstance()->generateHealth(-10, 10, "FullHealth.png", false);
	
}

/*----------------------------------------------------------------------------------------
	Instance Getter Methods
----------------------------------------------------------------------------------------*/
void setHealthBar(float percent) {
	
	
}

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
std::shared_ptr<ComplexSpriteinfo> Character::generateComplexSpriteInfo()
{
	std::shared_ptr<ComplexSpriteinfo> spriteInfo = std::make_shared<ComplexSpriteinfo>();

	spriteInfo->addInfo("squareidle.png", 8, 1);
	spriteInfo->addInfo("squareRun.png", 8, 1);
	spriteInfo->addInfo("squareRedAttack.png", 8, 1);
	spriteInfo->addInfo("squareWhiteAttack.png", 8, 1);
	spriteInfo->addInfo("squareHurt.png", 8, 1);

	return spriteInfo;
}

// Changes the sprite animation to running
void Character::playRunAnimation()
{
	if (getCurrentSprite() == ANIMATION_IDLE)
	{
		changeSprite(ANIMATION_RUN);
	}
}


// Changes the sprite animation to idling
void Character::endRunAnimation()
{
	if (getCurrentSprite() == ANIMATION_RUN) 
	{
		changeSprite(ANIMATION_IDLE);
	}
}


// Changes the sprite animation to the melee attack for one animation then returns back to idle
void Character::playMeleeAttackAnimation()
{
	changeSprite(ANIMATION_ATTACK_MELEE, ANIMATION_IDLE);
}


// Changes the sprite animation to the range attack for one animation then returns back to idle
void Character::playRangeAttackAnimation()
{
	changeSprite(ANIMATION_ATTACK_RANGE, ANIMATION_IDLE);
}

void Character::playHurtAnimation()
{
	changeSprite(ANIMATION_HURT, ANIMATION_IDLE);
}