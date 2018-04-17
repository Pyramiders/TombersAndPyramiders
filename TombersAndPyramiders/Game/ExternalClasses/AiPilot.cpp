#pragma

#include "AiPilot.h"
#include "Randomize.h"



int attackNumber = 0;
int randomNumber = 0;
int attackCount = 0;
void AiPilot::shouldFire()
{
	attackNumber = attackNumber % 6;
	attackCount = attackCount + 1;
	if (attackCount == 120)
	{
		attackNumber = Randomize::Random();
		attackCount = 0;
	}
	if (attackNumber == 1)
	{
		currentState = attack;
		//attackNumber = rand();
	}

}

void AiPilot::setController(BaseController* controller)
{
	BasePilot::setController(controller);


	m_characterController = static_cast<CharacterController*>(controller);
	//m_characterController1 = static_cast<CharacterController*>(controller);
}


void AiPilot::onStart()
{
	currentState = walk;
	//currentState = run;
}

void AiPilot::onUpdate(int ticks)
{

	switch (currentState)
	{
	case walk:
		m_characterController->move(*(getMovement() * ((float)ticks / (float)1000)));
		shouldFire();
		//currentState = run;
		break;
	case attack:
		m_characterController->useWeapon();
		currentState = walk;
		break;
	/*case run:
		m_characterController1->move(getMovement1());
		shouldFire();
		break;*/
	}


}

void AiPilot::onEnd()
{}


Vector2 AiPilot::getMovement()
{
	coun++;
	if (coun == 30)
	{
		randomNumber = Randomize::Random(0, 21);
		coun = 0;
	}
	if (randomNumber == 1)
	{
		movement.setX(-0.2f);
		//movement.setY(0.0f);
	}
	else if (randomNumber == 2)
	{
		movement.setX(0.2f);
		//movement.setY(0.0f);
	}
	else if (randomNumber == 3)
	{
		movement.setY(0.2f);
		//movement.setX(0.0f);
	}
	else if (randomNumber == 4 )
	{
		movement.setY(-0.2f);
		//movement.setX(0.0f);
	}
	if (randomNumber == 15 )
	{
		movement.setX(-0.3f);
		movement.setY(0.0f);
	}
	else if (randomNumber == 16)
	{
		movement.setX(0.3f);
		//movement.setY(0.0f);
	}
	else if (randomNumber == 17)
	{
		movement.setY(0.3f);
		movement.setX(0.0f);
	}
	else if (randomNumber == 18)
	{
		movement.setY(-0.3f);
		//movement.setX(0.0f);
	}

	/*else if (randomNumber == 5)
	{
		movement.setX(-0.2f);
		movement.setY(0.2f);
	}
	else if (randomNumber == 6)
	{
		movement.setX(0.2f);
		movement.setY(0.2f);
	}
	else if (randomNumber == 7)
	{
		movement.setX(-0.2f);
		movement.setY(-0.2f);
	}
	else if (randomNumber == 8)
	{
		movement.setX(0.2f);
		movement.setY(-0.2f);
	}*/

	return movement;

}


/*Vector2 AiPilot::getMovement1()
{
	int randomNumber = rand() % 4;
	//randomNumber = randomNumber % 4;
	coun = coun + 1;
	Vector2 movement1 = Vector2(0, 0);
	if (coun == 60)
	{
		randomNumber = rand();
		coun = 0;
	}
	if (randomNumber == 3)
	{
		movement1.setX(-0.3f);
	}
	else if (randomNumber == 4)
	{
		movement1.setX(0.3f);

	}
	else if (randomNumber == 2)
	{
		movement1.setY(0.3f);
	}
	else if (randomNumber == 1)
	{
		movement1.setY(-0.3f);
	}
	/*else if (randomNumber == 4)
	{
		movement1.setX(-0.3f);
		movement1.setY(0.3f);
	}
	else if (randomNumber == 7)
	{
		movement1.setX(0.3f);
		movement1.setY(0.3f);
	}
	else if (randomNumber == 8)
	{
		movement1.setX(-0.3f);
		movement1.setY(-0.3f);
	}
	else if (randomNumber == 6)
	{
		movement1.setX(0.3f);
		movement1.setY(-0.3f);
	}

	return movement1;
}*/