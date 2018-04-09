/*===================================================================================*//**
	SilverChestplate
	
	A weak silver chestplate.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseChestplate.h"

/*========================================================================================
	SilverChestplate	
========================================================================================*/
class SilverChestplate : public BaseChestplate
{
    /*----------------------------------------------------------------------------------------
		Static Fields
    ----------------------------------------------------------------------------------------*/
	private:
		const static float SILVER_CHESTPLATE_DAMAGE_MULTIPLIER;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        explicit SilverChestplate();

		virtual ~SilverChestplate() {};
};
