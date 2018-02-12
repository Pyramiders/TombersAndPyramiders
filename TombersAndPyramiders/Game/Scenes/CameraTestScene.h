#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"
#include <memory>
#include "CameraFollow.h"

class CameraTestScene : public Scene
{
private:


public:
	CameraTestScene();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();
};