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
const string BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME = "TempWoodenShortsword.png";
const bool BaseShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION = false;

const int BaseShortsword::SILVER_SHORTSWORD_DAMAGE = 35;
const string BaseShortsword::SILVER_SHORTSWORD_IMAGE_NAME = "TempSilverShortsword.png";
const bool BaseShortsword::SILVER_SHORTSWORD_DESTROY_ON_COLLISION = false;

const int BaseShortsword::GOLD_SHORTSWORD_DAMAGE = 50;
const string BaseShortsword::GOLD_SHORTSWORD_IMAGE_NAME = "TempGoldShortsword.png";
const bool BaseShortsword::GOLD_SHORTSWORD_DESTROY_ON_COLLISION = false;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseShortsword::BaseShortsword(int damage, string imageName, bool destroyOnCollision) :
	BaseMeleeWeapon{ damage, imageName, SHORTSWORD_COLLIDER_WIDTH, SHORTSWORD_COLLIDER_HEIGHT, 
	destroyOnCollision, SHORTSWORD_CRITICAL_HIT_CHANCE, SHORTSWORD_ATTACK_COOLDOWN_TIME,
	SHORTSWORD_X_OFFSET_FROM_HOLDER, SHORTSWORD_Y_OFFSET_FROM_HOLDER, SHORTSWORD_COLLIDER_SCALE }
{
	m_damagingRegion->getComponent<BoxCollider>()->setDisabled(true);
	m_damagingRegion->getTransform()->setScale(0);
	BaseItem::m_itemIcon = imageName;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseShortsword::setProperties(int damage, string imageName, bool destroyOnCollision)
{
	m_damage = damage;
	m_itemIcon = imageName;
	m_damagingRegion->destroy(m_damagingRegion);
	m_damagingRegion = GameManager::getInstance()->createGameObject<DamagingRegion>(false, damage, imageName,
		SHORTSWORD_COLLIDER_WIDTH, SHORTSWORD_COLLIDER_HEIGHT, SHORTSWORD_CRITICAL_HIT_CHANCE, destroyOnCollision, 
		0, 0, SHORTSWORD_COLLIDER_SCALE);
}
