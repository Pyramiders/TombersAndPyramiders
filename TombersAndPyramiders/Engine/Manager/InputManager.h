#pragma once

#include "GLHeaders.h"
#include <map>
#include <iostream>
#include <memory>
#include "Vector2.h"

class InputManager
{
public:
	enum KeyAction
	{
		NONE,
		PRESSED,
		HELD,
		RELEASED
	};

	static InputManager* getInstance();

	bool onKeyPressed(SDL_Keycode code);
	bool onKey(SDL_Keycode code);
	bool onKeyReleased(SDL_Keycode code);
	KeyAction getKeyState(SDL_Keycode code);
	void handlePolledEvent(SDL_Event event);
	void updateKeys();
	std::shared_ptr<Vector2> getMousePosition();
	KeyAction getMouseLeftButtonState();

private:

	static InputManager *s_instance;
	std::map<SDL_Keycode, KeyAction> m_keys;

};