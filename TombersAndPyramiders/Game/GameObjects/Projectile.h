/*===================================================================================*//**
	Projectile
	
	A Damaging region that is fired by a projectile weapon, moves, and destroys itself 
	after a set duration or after hitting something.
    
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "DamagingRegion.h"

/*========================================================================================
	Projectile	
========================================================================================*/
class Projectile : public DamagingRegion
{
	/*----------------------------------------------------------------------------------------
		Instance Fields
	----------------------------------------------------------------------------------------*/
	private:
		Vector2 m_velocity;
		float m_lifespan;

	/*----------------------------------------------------------------------------------------
		Resource Management
	----------------------------------------------------------------------------------------*/
	public:
		explicit Projectile() = delete;

		explicit Projectile(BaseWeapon* weapon, string imageName, float colliderWidth, float colliderHeight, 
			float spawnXPosition, float spawnYPosition, float spriteScale, 
			float xVelocity, float yVelocity, 
			float lifespan);

		virtual ~Projectile();

	
	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
	public:
		void onUpdate(int ticks);

	private:
		void updatePosition(int ticks);
		void updateLifespan(int ticks);
};
