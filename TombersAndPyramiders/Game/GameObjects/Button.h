#pragma once

#include "ComplexSprite.h"
#include "ComponentTemplate.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "SpawnManager.h"
#include "GameManager.h"
#include "Panel.h"
#include "AudioSource.h"

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
	std::shared_ptr<ComplexSpriteinfo> generateComplexSpriteInfo(string type);
	void virtual OnClicked();
	void OnHover();
	bool CheckHovering();

	void onStart() {};
	void onUpdate(int ticks) {

		std::ostringstream message;
		if (CheckHovering())
		{
			if (!m_isHovering)
			{
				m_isHovering = true;
				changeSprite(BUTTON_HOVER);
				OnHover();

				if (m_type == "Info")
				{
					m_controlPanel->setVisible(true);
				}
			}
		}
		else
		{
			if (m_isHovering)
			{
				m_isHovering = false;
				changeSprite(BUTTON);

				if (m_type == "Info")
				{
					m_controlPanel->setVisible(false);
				}
			}
		}

		if (CheckHovering() && (GetKeyState(VK_LBUTTON) & 0x80) != 0)
		{
			// Do something when clicked
			OnClicked();
		}
	};
	void onEnd() {};

};