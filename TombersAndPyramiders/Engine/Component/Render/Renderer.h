#pragma once

#include "Component.h"

class Renderer : public Component
{
protected:
	int layer;

public:
	Renderer(GameObject* gameObject);
	void setLayer(int newLayer);
	int getLayer();
	void onStart() {};
	void onUpdate(int ticks) {};
	void onEnd() {};
};