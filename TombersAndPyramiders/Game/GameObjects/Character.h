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
#include <string>

/*========================================================================================
Character Types
========================================================================================*/
enum CharacterType
{
	player,
	beetle,
	MAX
};

/*========================================================================================
	Character	
========================================================================================*/
class Character : public ComplexSprite
{
	#define ANIMATION_HURT 0
	#define ANIMATION_WALK 1
	#define ANIMATION_IDLE 2
	#define ANIMATION_ATTACK_MELEE 3
	#define ANIMATION_ATTACK_RANGE 4
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
    private:
		BoxCollider* m_boxCollider = nullptr;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit Character(BasePilot* basePilot, CharacterType type = player);

	/*----------------------------------------------------------------------------------------
		Instance Getter Methods
    ----------------------------------------------------------------------------------------*/
    public:
        
    
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
    public:


	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		void onUpdate(int ticks);
		bool playAnimation(int animID, int animReturn = -1);
		bool playRunAnimation();
		bool endRunAnimation();
		bool playMeleeAttackAnimation();
		bool playRangeAttackAnimation();
		bool playHurtAnimation();
		virtual void onEnd () {};
		virtual void onNetworkEnd ();

    private:
		/*--------------------
		Player Animation Logic
		--------------------*/
		enum State
		{
			WALK_UP = 0,
			WALK_LEFT = 1,
			WALK_DOWN = 2,
			WALK_RIGHT = 3,
			IDLE_UP = 4,
			IDLE_LEFT = 5,
			IDLE_DOWN = 6,
			IDLE_RIGHT = 7,
			HURT_UP = 8,
			HURT_LEFT = 9,
			HURT_DOWN = 10,
			HURT_RIGHT = 11,
			ATTACK_MELEE = 12,
			ATTACK_RANGE = 13,
			ENUM_MAX
		}currentState;

		std::string m_walk;
		std::string m_shoot;
		std::string m_slash;
		std::string m_walkUp = "WalkUp";
		std::string m_walkLeft = "WalkLeft";
		std::string m_walkDown = "WalkDown";
		std::string m_walkRight = "WalkRight";
		std::string m_shootUp = "ShootUp";
		std::string m_shootLeft = "ShootLeft";;
		std::string m_shootDown = "ShootDown";
		std::string m_shootRight = "ShootRight";
		std::string m_slashUp = "SlashUp";
		std::string m_slashLeft = "SlashLeft";
		std::string m_slashDown = "SlashDown";
		std::string m_slashRight = "SlashRight";
		std::string m_idleUp = "IdleUp";
		std::string m_idleLeft = "IdleLeft";
		std::string m_idleDown = "IdleDown";
		std::string m_idleRight = "IdleRight";

		std::shared_ptr<ComplexSpriteInfo> generateComplexSpriteInfo(CharacterType type = player);
};
