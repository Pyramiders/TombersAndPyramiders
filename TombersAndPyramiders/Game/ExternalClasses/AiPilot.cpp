#pragma
#include "AiPilot.h"
#include <cmath>
#include "Randomize.h"

int attackNumber = 0;
int randomNumber = 0;
int attackCount = 0;


//bool AiPilot::checkRange()
//{
//	attackNumber = attackNumber % 6;
//	attackCount = attackCount + 1;
//	if (attackCount == 120)
//	{
//		attackNumber = Randomize::Random();
//		attackCount = 0;
//	}
//	if (attackNumber == 1)
//	{
//		currentState = attack;
//		//attackNumber = rand();
//	}
//
//}

void AiPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);

	m_characterController = static_cast<CharacterController*>(controller);
}

void AiPilot::onStart()
{
	currentState = walk;
	//currentState = run;
}

void AiPilot::CheckingTimer()
{
	if (TimePassed >= 1.0f)
	{
		TimePassed = 0.0f;
		// Get a new target
		if (target == nullptr)
		{
			for (int i = 0; i < SpawnManager::getInstance()->allPlayers.size(); i++)
			{
				float distance = SpawnManager::getInstance()->allPlayers[i]->getTransform()->getDistance(m_characterController->getGameObject()->getTransform());
				if (distance < engageDistance)
				{
					target = SpawnManager::getInstance()->allPlayers[i];
				}
			}
		}
		else if(target != nullptr)
		{
			float distance = target->getTransform()->getDistance(m_characterController->getGameObject()->getTransform());

			if (distance > disengageDistance)
			{
				target = nullptr;
				currentState = walk;
			
			}
		}
	}
}

void AiPilot::onUpdate(int ticks)
{
	TimePassed =  TimePassed + (float)ticks / 1000.0f;
	CheckingTimer();

	movement = Vector2(0, 0);
	switch (currentState)
	{
	case walk:

		if (target == nullptr)
		{
			m_characterController->move(getRandomMovement());
			if (checkRange() == false)
			{
				currentState = attack;
			}
		}
		else
	/*	{
			m_characterController->move(getMovement());
			if (checkRange() == true)
			{
				currentState = melee;
			}
		}
		*/
		m_characterController->move(*(getMovement() * ((float)ticks / (float)1000)));
		checkRange();
		break;

	case attack:
		m_characterController->move(stopMovement());
		m_characterController->useWeapon();
		if (checkRange() == false)
		{
			currentState = walk;
		}
		break;

	/*case melee:
		m_characterController->move(stopMovement());
		m_characterController->useWeaponMelee();
		if (checkRange() == false)
		{
			currentState = walk;
		}
		break;*/
}
}

bool AiPilot::checkRange()
{
	if (target != nullptr)
	{
		float distance = target->getTransform()->getDistance(m_characterController->getGameObject()->getTransform());
		if (distance < stopDistance)
		{
			return true;
		}
	}

	return false;
}

/* bool checkPlayerStatus();
{
	if (target->Ghost)
	{
		target = nullptr;
		currentState = walk;
		return true;
	}
	return false;
}
*/
	

Vector2 AiPilot::getMovement()
{
	//m_characterController->updateSpeed(Vector2(1, 1));

	if (target != nullptr) {
		float myX = m_characterController->getGameObject()->getTransform()->getX();
		float myY = m_characterController->getGameObject()->getTransform()->getY();
		float targetX = target->getTransform()->getX();
		float targetY = target->getTransform()->getY();

		float x = abs(targetX - myX);
		float y = abs(targetY - myY);
		
		if (myX > targetX)
		{
			x = x *= -1;
		}
		if (myY > targetY)
		{
			y = y *= -1;
		}
		
		if (x < 0)
		{
			x = -0.3;
		}
		if (x > 0)
		{
			x = 0.3;
		}
		if (y < 0)
		{
			y = -0.3;
		}
		if (y > 0)
		{
			y = 0.3;
		}
		movement.setX(x);
		movement.setY(y);
	}

	return movement;
}

Vector2 AiPilot::getRandomMovement()
{
	coun++;
	if (coun == 30)
	{

		//randomNumber = rand() % 11;
		randomNumber = Randomize::Random(0, 21);
		coun = 0;
	}
	if (randomNumber == 1)
	{
		movement.setX(-0.02f);
	}
	else if (randomNumber == 2)
	{
		movement.setX(0.02f);
	}
	else if (randomNumber == 3)
	{
		movement.setY(0.02f);
		movement.setX(0.01f);
	}
	else if (randomNumber == 4 )
	{
		movement.setY(-0.02f);
		movement.setX(0.01f);
	}
	if (randomNumber == 5 )
	{
		movement.setX(-0.02f);
		movement.setY(-0.01f);
	}
	else if (randomNumber == 6)
	{
		movement.setX(0.02f);
		movement.setY(-0.01f);
	}
	else if (randomNumber == 7)
	{
		movement.setY(0.02f);
		movement.setX(0);
	}
	else if (randomNumber == 8)
	{
		movement.setY(-0.02f);
		movement.setX(0);
	}

	return movement;
}

 Vector2 AiPilot::stopMovement()
{
	movement.setX(0);
	movement.setY(0);

	return movement;
}

