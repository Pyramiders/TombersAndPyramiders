#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"
#include <memory>
#include "CameraFollow.h"

class PossessionTestScene : public Scene
{
private:


public:
	PossessionTestScene();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();
};