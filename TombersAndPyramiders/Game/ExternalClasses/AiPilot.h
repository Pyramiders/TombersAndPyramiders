#pragma once

#include <time.h>
#include "BasePilot.h"
#include "CharacterController.h"
#include "Vector2.h"
#include "Inventory.h"
#include "Character.h"
 #include "SpawnManager.h"

#define SPEED_LEFT -0.01f
#define SPEED_RIGHT 0.01f
#define SPEED_UP 0.01f
#define SPEED_DOWN -0.01f
#define SPEED 0.01f

class CharacterController;
class Vector2;
class AiPilot : public BasePilot
{

private:
	int coun = 0;
	CharacterController* m_characterController;
	Vector2 movement = Vector2(0, 0);

public:
	bool checkRange();
	//bool checkPlayerStatus();
	enum state
	{
		walk = 0,
		attack = 1,
		melee = 2
	}currentState;

	explicit AiPilot() = default;
	void setController(BaseController* controller);
	void onStart();
	void onUpdate(int ticks);
	void onEnd() {};
	
	void CheckingTimer();
	float engageDistance = 15;
	float disengageDistance = 20;
	float stopDistance = 3;
	float TimePassed = 0.0;

	std::shared_ptr<Character> target;
	Vector2 getMovement();
	Vector2 getRandomMovement();
	Vector2 stopMovement();
};
