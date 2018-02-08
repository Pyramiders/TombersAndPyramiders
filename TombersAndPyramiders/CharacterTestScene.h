#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Shader.h"
#include <memory>
#include "CameraFollow.h"

class CharacterTestScene : public Scene
{
private:


public:
	CharacterTestScene();
	void onStart();
	void onResume() {};
	void onUpdate(int ticks);
	void onPause();
	void onEnd();
	void setCameraFollow(std::shared_ptr<GameObject> toFollow);
};