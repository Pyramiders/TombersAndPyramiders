/*#include "AI.h"
#include "MatchManager.h"
#include "Vector2.h"
#include "Transform.h"
#include "AILearning.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "AudioManager.h"

AI::AI(GameObject* gameObject, bool _isLearning) : Component(gameObject)
{
	myBattler = (Battler*)GetGameObject();
	myTransform = myBattler->GetTransform();

	intelligence = 0.5f;
	courage = 0.5f;
	decisionFrequency = 1.0f;
	timeSinceLastDecision = 0.0f;
	lastActionWasShooting = true;

	currentState = idle;
	currentTarget = position;
	currentBehaviour = none;

	isLearning = _isLearning;
}

AI::~AI()
{
	MatchManager::GetInstance()->UnRegisterCharacter(myBattler);
}

void AI::Initialize(float _intelligence, float _courage, float _decisionFrequency)
{
	teamID = myBattler->stats.teamID;
	intelligence = _intelligence;
	courage = _courage;
	decisionFrequency = _decisionFrequency;
}

void AI::OnUpdate(int timeDelta) 
{
	float deltaTime = (float)timeDelta / 1000.0f;

	switch (currentState)
	{
		case idle:
			if (CanMakeDecision(deltaTime))
			{
				GetTarget();
			}
			break;
		case walk:
			if (currentTarget == battler)
			{
				MoveToTargetBattler(currentBehaviour == cower ? true : false);
			}
			else if (currentTarget == position)
			{
				if (isLearning)
				{
					SetLearnedVelocity();
				}
				else
				{
					MoveToTargetPosition(intelligence > courage ? true : false);
				}
			}
			break;
		case shoot:
			Shoot();
			currentState = idle;
			break;
		case dead:
			return;
		case s_MAX:
			break;
	}
}

void AI::GetTarget()
{
	currentBehaviour = none;

	float chanceToRunAway = randomFloatInRange(0.0f, 1.0f);
	if (chanceToRunAway > courage)
	{
		currentTarget = position;
		currentState = walk;
		int enemyTeamNumber = 1;
		if (teamID == 1)
		{
			enemyTeamNumber = 2;
		}
		std::vector<Battler*> enemyTeam = MatchManager::GetInstance()->GetTeam(enemyTeamNumber);
		if (enemyTeam.size() != 0) {
			targetPosition = GetTargetPosition();
		}
	}
	else
	{
		currentTarget = battler;
		currentState = walk;
		targetBattler = GetTargetBattler();
	}
}

GameObject* AI::GetTargetBattler()
{
	int enemyTeamNumber = 1;
	if (teamID == 1)
	{
		enemyTeamNumber = 2;
	}
	std::vector<Battler*> enemyTeam = MatchManager::GetInstance()->GetTeam(enemyTeamNumber);
	if (enemyTeam.size() == 0) {
		return nullptr;
	}
	int randomBattler = std::rand() % enemyTeam.size();

	return enemyTeam[randomBattler];
}

Vector2* AI::GetTargetPosition()
{
	float startPosXMax = getGameWidth() / 2;
	float startPosYMax = getGameHeight() / 2;
	float startPosXMin = getGameWidth() / 6;
	float startPosYMin = -startPosYMax;

	float posX = 0;
	float posY = 0;

	if (myBattler == NULL || myBattler == nullptr) {
		return nullptr;
	}

	if (teamID == 1)
	{
		posX = randomFloatInRange(-startPosXMin, -startPosXMax);
		posY = randomFloatInRange(startPosYMin, startPosYMax);
	}
	else if (teamID == 2)
	{
		posX = randomFloatInRange(startPosXMin, startPosXMax);
		posY = randomFloatInRange(startPosYMin, startPosYMax);
	}

	Vector2* battlefieldLocation = new Vector2(posX, posY);
	return battlefieldLocation;
}

void AI::MoveToTargetBattler(bool isRunning)
{
	if (targetBattler == nullptr || targetBattler == NULL) {
		GetTarget();
		if (targetBattler == nullptr || targetBattler == NULL) {
			return;
		}
	}
	if (targetBattler->GetTransform () == NULL)
		return;
	float targetPosY = targetBattler->GetTransform()->getY();
	float targetPosX = targetBattler->GetTransform()->getX();

	float myPosY = myTransform->getY();
	float myPosX = myTransform->getX();

	float posDiffY = targetPosY - myPosY;
	float posDiffX = targetPosX - myPosX;

	if (teamID == 2)
	{
		posDiffX *= -1;
	}

	float moveSpeed = isRunning ? myBattler->stats.runSpeed : myBattler->stats.moveSpeed;

	int directionY = (posDiffY > 0) ? 1 : -1;
	if (posDiffY >= (-1 + intelligence) && posDiffY <= (1 - intelligence))
	{
		currentState = shoot;
		return;
	}

	// Adds a little x movement which brings him closer to the target if his courage is high, and further away
	// if his courage is low.
	if (currentBehaviour == none)
		GetBehaviour();

	int directionX = 0;
	if (currentBehaviour == cower)
	{
		directionX = (teamID == 1) ? -1 : 1;
	}
	else if (currentBehaviour == engage)
	{
		directionX = (teamID == 1) ? 1 : -1;
	}
	if (posDiffX < MIN_DISTANCE_TO_TARGET_X - (courage * COURAGE_DISTANCE_X_MULTIPLIER))
	{
		//if (myBattler->stats.teamID == 1)
		//{
		//	cout << "TOO CLOSE!" << endl;
		//	cout << "Position Difference: " << posDiffX << endl;
		//}

		if (posDiffX > 2.0)
		{
			directionX = 0;
		}
		else
		{
			directionX = (teamID == 1) ? -1 : 1;
		}
	}
	//else
	//{
	//	if (myBattler->stats.teamID == 1)
	//		cout << "TOO FAR!" << endl;
	//}

	// Check if this would take the battler out of bounds, if it does then don't move x
	float posXToMoveTo = moveSpeed * directionX;
	if (!myBattler->Move(posXToMoveTo, moveSpeed * directionY, false, false))
	{
		posXToMoveTo = 0;
		myBattler->Move(posXToMoveTo, moveSpeed * directionY, false, false);
	}
}

void AI::MoveToTargetPosition(bool isRunning)
{
	float myPosY = myTransform->getY();
	float myPosX = myTransform->getX();

	if (targetPosition == nullptr) {
		return;
	}

	float posDiffY = targetPosition->getY() - myPosY;
	float posDiffX = targetPosition->getX() - myPosX;

	int directionY = (posDiffY > 0) ? 1 : -1;
	int directionX = (posDiffX > 0) ? 1 : -1;

	if ((posDiffY >= -1 && posDiffY <= 1) && (posDiffX >= -1 && posDiffX <= 1))
	{
		currentState = idle;
		return;
	}
	else if (posDiffY >= -1 && posDiffY <= 1)
	{
		directionY = 0;
	}
	else if (posDiffX >= -1 && posDiffX <= 1)
	{
		directionX = 0;
	}

	float moveSpeed = isRunning ? myBattler->stats.runSpeed : myBattler->stats.moveSpeed;

	if (!myBattler->Move(moveSpeed * directionX, moveSpeed * directionY, false, false))
	{
		currentState = idle;
	}
}

void AI::SetLearnedVelocity()
{
	vector<double> learnedDecisions;

	if (myBattler->stats.teamID == 1)
	{
		learnedDecisions = MatchManager::GetInstance()->teamOneNet.MakeDecision(myBattler);
	}
	else
	{
		learnedDecisions = MatchManager::GetInstance()->teamTwoNet.MakeDecision(myBattler);
	}

	myBattler->Move(learnedDecisions[1], learnedDecisions[2], false, false);
	currentState = idle;
}


void AI::Shoot()
{
	// The more intelligent the AI the higher chance he has to shoot
	float chanceOfFiring = randomFloatInRange(0.0f, 1.0f);
	float snowballStrength = targetBattler->GetTransform()->getX() - myTransform->getX();
	if (snowballStrength < 0.0f)
	{
		snowballStrength = -snowballStrength;
	}


	if (isLearning)
	{
		vector<double> learnedDecisions;

		if (myBattler->stats.teamID == 1)
		{
			learnedDecisions = MatchManager::GetInstance()->teamOneNet.MakeDecision(myBattler);
		}
		else
		{
			learnedDecisions = MatchManager::GetInstance()->teamTwoNet.MakeDecision(myBattler);
		}

		chanceOfFiring = learnedDecisions[0];
	}

	if (chanceOfFiring + intelligence >= 1)
	{
		myBattler->ThrowSnowball(snowballStrength);
		AudioManager::GetInstance()->PlaySEFshoot("./Game/Assets/shoot.wav", 1, 0.6f);
	}
}

bool AI::CanMakeDecision(float deltaTIme)
{
	timeSinceLastDecision += deltaTIme;
	if (timeSinceLastDecision >= decisionFrequency)
	{
		timeSinceLastDecision = 0.0f;
		return true;
	}

	return false;
}

void AI::GetBehaviour()
{
	float randomFloat = randomFloatInRange(0.0f, 1.0f);
	if (randomFloat < courage)
	{
		currentBehaviour = engage;
	}
	else
	{
		currentBehaviour = cower;
	}
}

void AI::Died()
{
	MatchManager::GetInstance()->UnRegisterCharacter(myBattler);
	currentState = dead;
}

void AI::Retarget() {
	GetTarget();
}
*/