/*===================================================================================*//**
	BaseController
	
	Abstract class for a component that controls the actions of an agent.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseController.h"
#include "BasePilot.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseController::BaseController(GameObject* gameObject, BasePilot* pilot) :
	Component(gameObject)
{
	setPilot(pilot);
}

/*----------------------------------------------------------------------------------------
	Instance Setter Methods
----------------------------------------------------------------------------------------*/
void BaseController::setPilot(BasePilot* pilot)
{
	m_pilot = std::unique_ptr<BasePilot>(pilot);
	
	if (m_pilot.get() != nullptr)
	{
		m_pilot.get()->setController(this);
	}
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseController::onStart()
{
	if (m_pilot.get() != nullptr)
	{
		m_pilot.get()->onStart();
	}
}

void BaseController::onUpdate(int ticks)
{
	if (m_pilot.get() != nullptr)
	{
		m_pilot.get()->onUpdate(ticks);
	}
}

void BaseController::onEnd()
{
	if (m_pilot.get() != nullptr)
	{
		m_pilot.get()->onEnd();
	}
}
