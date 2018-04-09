/*===================================================================================*//**
	GoldGreaves
	
	A pair of simple gold greaves.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseGreaves.h"
class Vector2;

/*========================================================================================
	GoldGreaves	
========================================================================================*/
class GoldGreaves : public BaseGreaves

{
    /*----------------------------------------------------------------------------------------
		Static Fields
    ----------------------------------------------------------------------------------------*/
	private:
		static const float GOLD_GREAVES_COOLDOWN_TIME;
		static const float GOLD_GREAVES_DASH_DURATION;
		static const float GOLD_GREAVES_MAX_DASH_SPEED;
		
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	private:
		float m_timeLeftInDash;
		std::unique_ptr<Vector2> m_dashDirection;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit GoldGreaves();

		~GoldGreaves() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual void onStart();
		void effect(int ticks);
};