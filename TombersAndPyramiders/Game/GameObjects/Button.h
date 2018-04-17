#pragma once

#include "ComplexSprite.h"
#include "ComponentTemplate.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "SpawnManager.h"
#include "GameManager.h"
#include "Panel.h"
#include "AudioSource.h"
#include <iostream>

#define BUTTON 0
#define BUTTON_HOVER 1

class Button : public ComplexSprite
{
private:
	float m_x, m_y, m_z, m_width, m_height;
	string m_type;
	std::shared_ptr<Panel> m_controlPanel;
	std::shared_ptr<AudioSource> m_soundEffect;
	bool m_isHovering = false;
public:
	Button(float x, float y, float z, float width, float height, string type);
	~Button();
	std::shared_ptr<ComplexSpriteInfo> generateComplexSpriteInfo(string type);
	void virtual OnClicked();
	void OnHover();
	bool CheckHovering();

	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};

};