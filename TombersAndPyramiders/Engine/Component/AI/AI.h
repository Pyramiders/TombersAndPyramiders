#pragma once

#include "Component.h"
#include "GameObject.h"
//#include "Battler.h"
#include "Transform.h"

class AI :
	public Component
{
private:
	float MIN_DISTANCE_TO_TARGET_X = 13.0f;
	float COURAGE_DISTANCE_X_MULTIPLIER = 5.0f;

	//Battler *myBattler;
	Transform *myTransform;

	Vector2 *targetPosition;
	void GetTarget();
	GameObject* GetTargetBattler();
	Vector2* GetTargetPosition();

	enum State
	{
		idle = 0,
		walk = 1,
		shoot = 2,
		dead = 3,
		s_MAX
	}currentState;
	void MoveToTargetBattler(bool isRunning);
	void MoveToTargetPosition(bool isRunning);
	void SetLearnedVelocity();
	void Shoot();

	enum Behaviour
	{
		none = 0,
		cower = 1,
		engage = 2,
		b_MAX
	}currentBehaviour;
	void GetBehaviour();
	bool CanMakeDecision(float deltaTIme);

	float decisionFrequency;
	float timeSinceLastDecision;
	bool lastActionWasShooting;

	float intelligence;
	float courage;

	bool isLearning;
	int teamID;

public:
	AI(GameObject* gameObject, bool _isLearning);
	~AI();
	void Initialize(float _intelligence, float _courage, float _decisionFrequency);
	void Died();
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
	void Retarget();

	enum Target
	{
		battler = 0,
		position = 1,
		t_MAX
	}currentTarget;
	GameObject *targetBattler;
};

