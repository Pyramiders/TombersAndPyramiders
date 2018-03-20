#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class MainMenuScene : public Scene
{
private:

public:
	MainMenuScene();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();
	
};