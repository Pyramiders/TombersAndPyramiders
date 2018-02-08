#pragma once

#include "GameScene.h"
#include "GameObject.h"
#include "Shader.h"

class AudioTestScene : public GameScene {
private:
	Shader* ourShader;

public:
	void OnStart();
	void OnResume() {};
	void OnUpdate(int ticks);
	void OnPause() {};
	void OnEnd();

};
