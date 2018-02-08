/*===================================================================================*//**
	BasePilot
	
	Abstract class for an object that either generates or fetches input for a 
	BaseController.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BasePilot.h"

/*----------------------------------------------------------------------------------------
	Instance Setter Methods
----------------------------------------------------------------------------------------*/
void BasePilot::setController(BaseController* controller)
{
	m_controller = controller;
}
