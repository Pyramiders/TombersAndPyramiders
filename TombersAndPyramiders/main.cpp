//Using SDL and standard IO
#include <stdio.h>
#include <string>
#include <iostream>
#include "GameManager.h"
#include "SpriteRendererManager.h"
#include "GameObject.h"
#include "AudioManager.h"
#include "GLHeaders.h"
#include "NetworkingManager.h"

void RunGame();

int main(int argc, char *argv[])
{
	//For Visual Studio std::cout outputs
//#if defined _WIN32 || defined _WIN64
//	AllocConsole();
//	freopen("CONOUT$", "w", stdout);
//	freopen("CONOUT$", "w", stderr);
//#endif

  //AudioManager audioManager;
  //audioManager.PlaySoundEffect("mario_.mp3");
  if (!SpriteRendererManager::getInstance()->init()) {
    return -1;
  }

  //TODO, not handle this in command line
  if (argc < 2) {
	  std::cout << "Networking Join Directed to IP " << DEFAULT_IP << ":" << DEFAULT_PORT << std::endl;
  }
  if (argc > 1) {
	  NetworkingManager::getInstance ()->setIP (argv[1]);
	  std::cout << "Networking Join Directed to IP " << argv[1] << ":" << DEFAULT_PORT << std::endl;
	  if (argc > 2) {
		  NetworkingManager::getInstance ()->setIP (argv[1], atoi (argv[2]));
		  std::cout << "Networking Join Directed to IP " << argv[1] << ":" << argv[2] << std::endl;
	  }
  }

  RunGame ();
  SpriteRendererManager::getInstance()->cleanup ();
  delete(SpriteRendererManager::getInstance ());

	return 0;
}

void RunGame()
{
  GameManager::getInstance();
  SpriteRendererManager::getInstance();
  //GameManager::GetInstance()->BeginLoop(new SceneTemplate());
  GameManager::getInstance()->onStart();
}
