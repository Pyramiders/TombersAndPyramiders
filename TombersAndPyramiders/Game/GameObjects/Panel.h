#pragma once

#include "GameObject.h"
#include "ComponentTemplate.h"
#include "ComplexSprite.h"

#define INVISIBLE 0
#define VISIBLE 1

//Instance/MovableCharacter
class Panel : public ComplexSprite
{
private:
	////Private Variables
	float m_x, m_y, m_width, m_height;
	string m_image;
	////Private Methods

public:
	////Public Variables

	////Public Methods
	//The constructor that is called on creation
	Panel(float x, float y, float width, float height, string type);
	//The destructor that is called on deletion
	~Panel();
	//Any public methods you want other Components/GameObjects to have access too
	std::shared_ptr<ComplexSpriteInfo> generateComplexSpriteInfo(string type);
	void setVisible(bool set);

	void onStart() {};
	void onUpdate(int ticks) {};
	void onEnd() {};

};