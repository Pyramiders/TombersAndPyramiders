#include "InputManager.h"

InputManager* InputManager::s_instance;

InputManager* InputManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new InputManager();
	return s_instance;
}

bool InputManager::onKeyPressed(SDL_Keycode code)
{
	std::map<SDL_Keycode, KeyAction>::iterator it = m_keys.find(code);
	if (it != m_keys.end())
		return it->second == InputManager::KeyAction::PRESSED;
	return false;
}

bool InputManager::onKey(SDL_Keycode code)
{
	std::map<SDL_Keycode, KeyAction>::iterator it = m_keys.find(code);
	if (it != m_keys.end())
		return it->second != InputManager::KeyAction::NONE;
	return false;
}

bool InputManager::onKeyReleased(SDL_Keycode code)
{
	std::map<SDL_Keycode, KeyAction>::iterator it = m_keys.find(code);
	if (it != m_keys.end())
		return it->second == InputManager::KeyAction::RELEASED;
	return false;
}

InputManager::KeyAction InputManager::getKeyState(SDL_Keycode code)
{
	std::map<SDL_Keycode, KeyAction>::iterator it = m_keys.find(code);
	if (it != m_keys.end())
		return it->second;
	else
		return InputManager::KeyAction::NONE;
}

void InputManager::updateKeys()
{
	for (std::map<SDL_Keycode, KeyAction>::iterator it = m_keys.begin(); it != m_keys.end(); ++it)
	{
		if (it->second == InputManager::KeyAction::PRESSED)
			it->second = InputManager::KeyAction::HELD;
		if (it->second == InputManager::KeyAction::RELEASED)
			it->second = InputManager::KeyAction::NONE;
	}
}

void InputManager::handlePolledEvent(SDL_Event event)
{
	SDL_Keycode code;
	std::map<SDL_Keycode, KeyAction>::iterator it;

	switch (event.type)
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		code = event.key.keysym.sym;
		it = m_keys.find(code);
		if (event.type == SDL_KEYDOWN)
			if (it == m_keys.end() || (it != m_keys.end() && it->second != InputManager::KeyAction::HELD))
				m_keys[code] = InputManager::KeyAction::PRESSED;
		if (event.type == SDL_KEYUP)
			if (it != m_keys.end() && it->second == InputManager::KeyAction::HELD)
				m_keys[code] = InputManager::KeyAction::RELEASED;
		break;
	default:
		break;
	}
}

std::shared_ptr<Vector2> InputManager::getMousePosition()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	return std::make_shared<Vector2>(x, y);
}

InputManager::KeyAction InputManager::getMouseLeftButtonState()
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		return InputManager::KeyAction::PRESSED;
	}
	return InputManager::KeyAction::NONE;
}