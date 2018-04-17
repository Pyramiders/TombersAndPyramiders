/*===================================================================================*//**
	WoodenShield
	
	A weak wooden shield.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "WoodenShield.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const string WoodenShield::WOODEN_SHIELD_IMAGE_NAME = "TempWoodenShield.png";
const float WoodenShield::WOODEN_SHIELD_DAMAGE_MULT = 0.9f;
const float WoodenShield::WOODEN_SHIELD_COOLDOWN_TIME = 0.5f;

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
WoodenShield::WoodenShield() :
	BaseShield(WOODEN_SHIELD_IMAGE_NAME, WOODEN_SHIELD_DAMAGE_MULT, WOODEN_SHIELD_COOLDOWN_TIME)
{
	m_itemIcon = "AddMeLater.png";
}
