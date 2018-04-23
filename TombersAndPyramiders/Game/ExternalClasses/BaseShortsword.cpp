/*===================================================================================*//**
	BaseShortsword
	Abstract class for a base shortsword.
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseShortsword.h"
#include "BoxCollider.h"
#include "GameManager.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const float BaseShortsword::SHORTSWORD_COLLIDER_WIDTH = 1;
const float BaseShortsword::SHORTSWORD_COLLIDER_HEIGHT = 1;
const float BaseShortsword::SHORTSWORD_COLLIDER_SCALE = 10;
const float BaseShortsword::SHORTSWORD_X_OFFSET_FROM_HOLDER = 1;
const float BaseShortsword::SHORTSWORD_Y_OFFSET_FROM_HOLDER = 0;
const float BaseShortsword::SHORTSWORD_CRITICAL_HIT_CHANCE = 0.05f;
const float BaseShortsword::SHORTSWORD_ATTACK_COOLDOWN_TIME = 0.5f;

const int BaseShortsword::WOODEN_SHORTSWORD_DAMAGE = 20;
const string BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME = "shortswordIcon.png";
const bool BaseShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION = false;

const int BaseShortsword::SILVER_SHORTSWORD_DAMAGE = 35;
const string BaseShortsword::SILVER_SHORTSWORD_IMAGE_NAME = "shortswordIcon.png";
const bool BaseShortsword::SILVER_SHORTSWORD_DESTROY_ON_COLLISION = false;

const int BaseShortsword::GOLD_SHORTSWORD_DAMAGE = 50;
const string BaseShortsword::GOLD_SHORTSWORD_IMAGE_NAME = "shortswordGoldIcon.png";
const bool BaseShortsword::GOLD_SHORTSWORD_DESTROY_ON_COLLISION = false;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseShortsword::BaseShortsword(int damage, string imageName, bool destroyOnCollision) :
	BaseMeleeWeapon{ damage, "empty.png", SHORTSWORD_COLLIDER_WIDTH, SHORTSWORD_COLLIDER_HEIGHT, 
	destroyOnCollision, SHORTSWORD_CRITICAL_HIT_CHANCE, SHORTSWORD_ATTACK_COOLDOWN_TIME,
	SHORTSWORD_X_OFFSET_FROM_HOLDER, SHORTSWORD_Y_OFFSET_FROM_HOLDER, SHORTSWORD_COLLIDER_SCALE }
{
	m_damagingRegion->getComponent<BoxCollider>()->setDisabled(true);
	m_damagingRegion->getTransform()->setScale(0);
	BaseItem::m_itemIcon = imageName;
	setupSprites(imageName);
	m_zIndex = 102;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseShortsword::setProperties(int damage, string imageName, bool destroyOnCollision)
{
	m_damage = damage;
	m_itemIcon = "empty.png";
	m_damagingRegion->destroy(m_damagingRegion);
	m_damagingRegion = GameManager::getInstance()->createGameObject<DamagingRegion>(false, damage, "empty.png",
		SHORTSWORD_COLLIDER_WIDTH, SHORTSWORD_COLLIDER_HEIGHT, SHORTSWORD_CRITICAL_HIT_CHANCE, destroyOnCollision, 
		0, 0, SHORTSWORD_COLLIDER_SCALE);
}

/*----------------------------------------------------------------------------------------
| Setup Sprites and Animations
----------------------------------------------------------------------------------------*/
void BaseShortsword::setupSprites(std::string identifier)
{
	spriteInfo = std::make_shared<ComplexSpriteInfo>();

	if (identifier == BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME)
	{
		addSprite("Player/Attack/Melee/sword.png", "walk", 6, 4);
		addAnimation("walk", "WalkUp", 0, 0);
		addAnimation("walk", "WalkLeft", 6, 6);
		addAnimation("walk", "WalkDown", 12, 12);
		addAnimation("walk", "WalkRight", 18, 18);
		addAnimation("walk", "IdleUp", 0, 0);
		addAnimation("walk", "IdleLeft", 6, 6);
		addAnimation("walk", "IdleDown", 12, 12);
		addAnimation("walk", "IdleRight", 18, 18);

		addSprite("Player/Attack/Melee/sword.png", "slash", 6, 4);
		addAnimation("slash", "SlashUp", 1, 5);
		addAnimation("slash", "SlashLeft", 7, 11);
		addAnimation("slash", "SlashDown", 13, 17);
		addAnimation("slash", "SlashRight", 19, 23);
		addAnimation("slash", "IdleUp", 0, 0);
		addAnimation("slash", "IdleLeft", 6, 6);
		addAnimation("slash", "IdleDown", 12, 12);
		addAnimation("slash", "IdleRight", 18, 18);
	}
	else if (identifier == BaseShortsword::SILVER_SHORTSWORD_IMAGE_NAME)
	{
		addSprite("Player/Attack/Melee/sword.png", "walk", 6, 4);
		addAnimation("walk", "WalkUp", 0, 0);
		addAnimation("walk", "WalkLeft", 6, 6);
		addAnimation("walk", "WalkDown", 12, 12);
		addAnimation("walk", "WalkRight", 18, 18);
		addAnimation("walk", "IdleUp", 0, 0);
		addAnimation("walk", "IdleLeft", 6, 6);
		addAnimation("walk", "IdleDown", 12, 12);
		addAnimation("walk", "IdleRight", 18, 18);

		addSprite("Player/Attack/Melee/sword.png", "slash", 6, 4);
		addAnimation("slash", "SlashUp", 1, 5);
		addAnimation("slash", "SlashLeft", 7, 11);
		addAnimation("slash", "SlashDown", 13, 17);
		addAnimation("slash", "SlashRight", 19, 23);
		addAnimation("slash", "IdleUp", 0, 0);
		addAnimation("slash", "IdleLeft", 6, 6);
		addAnimation("slash", "IdleDown", 12, 12);
		addAnimation("slash", "IdleRight", 18, 18);
	}
	else if (identifier == BaseShortsword::GOLD_SHORTSWORD_IMAGE_NAME)
	{
		spriteInfo = std::make_shared<ComplexSpriteInfo>();

		addSprite("Player/Attack/Melee/sword_gold.png", "walk", 6, 4);
		addAnimation("walk", "WalkUp", 0, 0);
		addAnimation("walk", "WalkLeft", 6, 6);
		addAnimation("walk", "WalkDown", 12, 12);
		addAnimation("walk", "WalkRight", 18, 18);
		addAnimation("walk", "IdleUp", 0, 0);
		addAnimation("walk", "IdleLeft", 6, 6);
		addAnimation("walk", "IdleDown", 12, 12);
		addAnimation("walk", "IdleRight", 18, 18);

		addSprite("Player/Attack/Melee/sword_gold.png", "slash", 6, 4);
		addAnimation("slash", "SlashUp", 1, 5);
		addAnimation("slash", "SlashLeft", 7, 11);
		addAnimation("slash", "SlashDown", 13, 17);
		addAnimation("slash", "SlashRight", 19, 23);
		addAnimation("slash", "IdleUp", 0, 0);
		addAnimation("slash", "IdleLeft", 6, 6);
		addAnimation("slash", "IdleDown", 12, 12);
		addAnimation("slash", "IdleRight", 18, 18);
	}

}