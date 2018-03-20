/*===================================================================================*//**
	WoodenShortsword

	Abstract class for a base shortsword.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "WoodenShortsword.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const int WoodenShortsword::WOODEN_SHORTSWORD_DAMAGE = 20;
const string WoodenShortsword::WOODEN_SHORTSWORD_IMAGE_NAME = "TempWoodenShortsword.png";
const bool WoodenShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION = false;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
WoodenShortsword::WoodenShortsword() :
	BaseShortsword{ WOODEN_SHORTSWORD_DAMAGE, WOODEN_SHORTSWORD_IMAGE_NAME, WOODEN_SHORTSWORD_DESTROY_ON_COLLISION }
{
	m_itemIcon = "WoodenShortsword.png";
}
