/*===================================================================================*//**
	SilverGreaves
	
	A pair of weak silver greaves.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "SilverGreaves.h"
#include "GameObject.h"
#include "Vector2.h"
#include "CharacterController.h"
#include <memory>

/*----------------------------------------------------------------------------------------
Static Fields
----------------------------------------------------------------------------------------*/
const float SilverGreaves::SILVER_GREAVES_COOLDOWN_TIME = 0.9f;
const float SilverGreaves::SILVER_GREAVES_DASH_DURATION = 0.6f;
const float SilverGreaves::SILVER_GREAVES_MAX_DASH_SPEED = 40.0f;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
SilverGreaves::SilverGreaves() :
	BaseGreaves(SILVER_GREAVES_COOLDOWN_TIME), 
	m_timeLeftInDash{ 0.0f }, 
	m_dashDirection{ make_unique<Vector2>() }
{
	m_itemIcon = "AddMeLater.png";
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void SilverGreaves::onStart()
{
	BaseGreaves::onStart();
	m_timeLeftInDash = SILVER_GREAVES_DASH_DURATION;
}

void SilverGreaves::effect(int ticks)
{
	if (m_timeLeftInDash > 0)
	{
		auto dashRotation = owner()->getTransform()->getRotation();
		auto dashAmount = ((float)ticks / 1000.0f) * SILVER_GREAVES_MAX_DASH_SPEED;
		//auto lerpFactor = (SILVER_GREAVES_DASH_DURATION - m_timeLeftInDash) / SILVER_GREAVES_DASH_DURATION;
		//dashAmount *= (1 - lerpFactor);

		auto dashDirection = Vector2(1, 0);
		dashDirection.rotate(dashRotation);
		Vector2* pDashDuration = dashDirection * dashAmount;

		//owner()->getTransform()->addTranslation(pDashDuration->getX(), pDashDuration->getY());
		//owner()->getComponent<Rigidbody>()->setVelocity(*pDashDuration);
		owner()->getComponent<CharacterController>()->move(*pDashDuration);
		m_timeLeftInDash -= (float)ticks / 1000.0f;
	}
}
