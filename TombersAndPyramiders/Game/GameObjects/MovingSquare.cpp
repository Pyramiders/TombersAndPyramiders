#include "MovingSquare.h"
#include "InputManager.h"

/*
Constructor called when the GameObject is created. Any GameObject specific creation code can go here.
This includes adding relevant components or any setup.

By default, GameObject's base class has a Transform component
*/
MovingSquare::MovingSquare() : SimpleSprite("IceTile.png", 0, 0)
{
	//Adding a base component. You create the new Component, pass it 'this', cast to a Component* then add it
	addComponent<ComponentTemplate>(this);

}

MovingSquare::~MovingSquare()
{
}

void MovingSquare::onUpdate(int ticks) {
	if (InputManager::getInstance()->onKey(SDLK_a))
	{
		this->getTransform()->addX(-0.15f);
	}
	if (InputManager::getInstance()->onKey(SDLK_d))
	{
		this->getTransform()->addX(0.15f);
	}
	if (InputManager::getInstance()->onKey(SDLK_w))
	{
		this->getTransform()->addY(0.15f);
	}
	if (InputManager::getInstance()->onKey(SDLK_s))
	{
		this->getTransform()->addY(-0.15f);
	}
};