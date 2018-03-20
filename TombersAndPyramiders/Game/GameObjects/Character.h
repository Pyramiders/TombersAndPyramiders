/*===================================================================================*//**
	Character
	
	Prefab class for any character.
    
    Copyright 2017 Erick Fernandez de Arteaga. All rights reserved.
        https://www.linkedin.com/in/erick-fda
        https://bitbucket.org/erick-fda
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "SimpleSprite.h"
#include "BoxCollider.h"
#include "ComplexSprite.h"
#include "BasePilot.h"
#include "Health.h"

/*========================================================================================
	Player Animation Defines
========================================================================================*/
#define ANIMATION_IDLE 0
#define ANIMATION_RUN 1
#define ANIMATION_ATTACK_MELEE 2
#define ANIMATION_ATTACK_RANGE 3
#define ANIMATION_HURT 4

/*========================================================================================
	Character	
========================================================================================*/
class Character : public ComplexSprite
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
    private:
		BoxCollider* m_boxCollider = nullptr;
		std::shared_ptr<Health> m_health;
		int m_maxHealth;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit Character(BasePilot* basePilot);

	/*----------------------------------------------------------------------------------------
		Instance Getter Methods
    ----------------------------------------------------------------------------------------*/
    public:
		void setHealthBar(float percent);
    
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
    public:


	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		void onUpdate(int ticks);
		void playRunAnimation();
		void endRunAnimation();
		void playMeleeAttackAnimation();
		void playRangeAttackAnimation();
		void playHurtAnimation();

    private:
		/*--------------------
		Player Animation Logic
		--------------------*/
		std::shared_ptr<ComplexSpriteinfo> generateComplexSpriteInfo();
};
