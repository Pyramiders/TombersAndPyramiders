#include "Button.h"
#include <string>
#include "SpriteRendererManager.h"
#include "GLHeaders.h"
#include "NetworkingManager.h"
#include "SpawnManager.h"

Button::Button(float x, float y, float z, float width, float height, string type) : ComplexSprite(generateComplexSpriteInfo(type), x / 25, y / 25, z, 10)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_width = width;
	m_height = height;
	m_type = type;
	if (type == "Info")
		m_controlPanel = dynamic_pointer_cast<Panel>(GameManager::getInstance()->createGameObject<Panel>(false, 0, 0, 512, 384, "Controls"));
	m_soundEffect = addComponent<AudioSource>(this);
}

Button::~Button()
{

}

std::shared_ptr<ComplexSpriteInfo> Button::generateComplexSpriteInfo(string type)
{
	std::shared_ptr<ComplexSpriteInfo> spriteInfo = std::make_shared<ComplexSpriteInfo>();
	spriteInfo->addSprite(type + "Button.png", "Button", 1, 1);
	spriteInfo->addSprite(type + "ButtonHover.png", "ButtonHover", 1, 1);
	return spriteInfo;
}

void Button::OnClicked()
{
	if (m_type == "Start")
	{
		if (NetworkingManager::getInstance()->startGame()) // TODO-ERICK Uncomment this before pushing
			SpawnManager::getInstance()->sendStartPacket();
	}
	else if (m_type == "Host")
		NetworkingManager::getInstance()->createHost();
	else if (m_type == "Join")
		NetworkingManager::getInstance()->createClient();
	else if (m_type == "Info") { }
	else if (m_type == "Exit")
		exit(0);
}

void Button::OnHover()
{
	std::cout << m_soundEffect << std::endl;
	std::cout << SFX_BUTTON_HOVER << std::endl;
	m_soundEffect->playSFX(SFX_BUTTON_HOVER);
}

bool Button::CheckHovering()
{
	auto mousePosition = InputManager::getInstance()->getMousePosition();
	mousePosition->setX(mousePosition->getX() - SCREEN_WIDTH / 2);
	mousePosition->setY(-mousePosition->getY() + SCREEN_HEIGHT / 2);
	return	mousePosition->getX() >= m_x - m_width / 2 &&
		mousePosition->getX() <= m_x + m_width / 2 &&
		mousePosition->getY() >= m_y - m_height / 2 &&
		mousePosition->getY() <= m_y + m_height / 2;
}

void Button::onUpdate(int ticks) {
	std::ostringstream message;
	if (CheckHovering())
	{
		if (!m_isHovering)
		{
			m_isHovering = true;
			changeSpriteSheet(BUTTON_HOVER);
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
			changeSpriteSheet(BUTTON);

			if (m_type == "Info")
			{
				m_controlPanel->setVisible(false);
			}
		}
	}
	if (CheckHovering() && InputManager::getInstance()->getMouseLeftButtonState() == InputManager::KeyAction::PRESSED)
	{
		// Do something when clicked
		OnClicked();
	}
}