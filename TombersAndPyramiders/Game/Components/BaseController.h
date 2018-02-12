/*===================================================================================*//**
	BaseController
	
	Abstract class for a component that controls the actions of an agent.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include <memory>
#include "Component.h"
#include "Character.h"

class GameObject;
class BasePilot;

/*========================================================================================
	BaseController	
========================================================================================*/
class BaseController : public Component
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		std::unique_ptr<BasePilot> m_pilot;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        explicit BaseController() = delete;

		explicit BaseController(GameObject* parentGameobject, BasePilot* pilot);

		virtual ~BaseController() {};
		
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
	public:
		void setPilot(BasePilot* pilot);

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
	public:
		/**
			Forwards the onStart() call to the pilot.
		*/
		virtual void onStart();

		/**
			Forwards the onUpdate() call to the pilot.
		*/
		virtual void onUpdate(int ticks);

		/**
			Forwards the onEnd() call to the pilot.
		*/
		virtual void onEnd();
};
