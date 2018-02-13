#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"

class SceneTemplate : public Scene
{
private:

public:
	SceneTemplate();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();
};