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
}
