#pragma once

#include "BasePilot.h"
#include <memory>

extern class BasePossessableController;

class Vector2;

class GhostPilot : public BasePilot
{
private:
	BaseController* m_ghostController; //The GhostCharacter's GhostController that was set on setController at the start
	std::shared_ptr<BasePossessableController> m_possessableController; //The Possessable object we may be controlling
	bool m_possessing;

	//Used in case, on swap, that other object gets an update on the same frame which swaps back before InputManager refreshed
	bool m_justSwapped;

	bool checkShouldSwap();
	
public:
	/** Default constructor. */
	GhostPilot();

public:

public:
	void onStart();

	void onUpdate(int ticks);

	void onEnd();
	void setController(BaseController* controller);

private:
	Vector2 getMovement();
};
