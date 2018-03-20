#include "Game.h"
#include "NetworkingManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <iostream>
#include "CharacterTestScene.h"
#include "LaunchScene.h"
#include "MainMenuScene.h"
#include "NetworkedGameScene.h"
#include "PossessionTestScene.h"

/*
This class is not intended to have a lot of code. This is intended to be the on entry call for
the game code, custom game manager update calls, and cleanup on exit.

The heirachy of Updates begin at main.cpp.
main.cpp initializes engine managers and starts the GameManager.cpp main loop.
GameManager.cpp updates engine managers, Game.cpp update, then the global game objects, and finally the current scene on SceneManager.cpp.
The Game.cpp update calls specific managers made to exist for the game.
The SceneManager.cpp calls its update on all game objects that exist for that scene.
Each GameObject cycles through and updates each one of their game components.
*/

void Game::onStart()
{
	SceneManager::getInstance()->pushScene(new MainMenuScene());
}

void Game::onUpdate(int ticks)
{
}

void Game::onEnd()
{

}