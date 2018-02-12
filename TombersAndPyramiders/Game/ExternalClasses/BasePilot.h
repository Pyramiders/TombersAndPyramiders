/*===================================================================================*//**
	BasePilot
	
	Abstract class for an object that either generates or fetches input for a 
	BaseController.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Updateable.h"
class BaseController;

/*========================================================================================
	BasePilot	
========================================================================================*/
class BasePilot : Updateable
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	BaseController* m_controller; /* Note this is delibrately a raw pointer. 
										Pilots do not own their controllers and should not delete them. */

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BasePilot() = default;

		virtual ~BasePilot() {};
		
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
	public:
		virtual void setController(BaseController* controller);

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual void onStart() = 0;
		virtual void onUpdate(int ticks) = 0;
		virtual void onEnd() = 0;
};
