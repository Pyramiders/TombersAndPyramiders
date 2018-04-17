#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"
#include "CameraFollow.h"
#include "Character.h"

class OldTestScene : public Scene
{
private:

public:
	std::map<Uint32, Character> players;
	OldTestScene();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();

};