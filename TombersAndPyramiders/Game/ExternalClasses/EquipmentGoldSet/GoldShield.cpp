/*===================================================================================*//**
	GoldShield
	
	A weak gold shield.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "GoldShield.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const string GoldShield::GOLD_SHIELD_IMAGE_NAME = "TempGoldShield.png";
const float GoldShield::GOLD_SHIELD_DAMAGE_MULT = 0.5f;
const float GoldShield::GOLD_SHIELD_COOLDOWN_TIME = 0.3f;

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
GoldShield::GoldShield() :
	BaseShield(GOLD_SHIELD_IMAGE_NAME, GOLD_SHIELD_DAMAGE_MULT, GOLD_SHIELD_COOLDOWN_TIME)
{
	m_itemIcon = "AddMeLater.png";
}
