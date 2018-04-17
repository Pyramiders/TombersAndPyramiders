#pragma once

#include "BasePilot.h"
#include <memory>
#include "Vector2.h"
#include "BasePossessableController.h"

class GhostReceiverPilot : public BasePilot
{
private:
	Vector2 m_lastNetworkVector;
	int m_updatesUntilInvalid;
	int m_updatesSinceNewMovement;
	bool m_hasInit;
	std::shared_ptr<BasePossessableController> m_possessableController;
	bool m_possessing;
	BaseController* m_ghostController;

public:
	/** Default constructor. */
	GhostReceiverPilot();

public:

public:
	void onStart();

	void onUpdate(int ticks);

	void onEnd();
	void setMovement(Vector2 vec, int updates);
	void setPossession(std::shared_ptr<BasePossessableController> possession);
	void setController(BaseController* controller);
	void tryTrigger();
	void movePossessable(Vector2 movement);
};
