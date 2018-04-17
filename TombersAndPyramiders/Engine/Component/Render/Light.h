#pragma once

#include "Component.h"

class Light : public Component
{
private:
    float m_size;
    int m_red;
    int m_green;
    int m_blue;

public:
    Light(GameObject* gameObject);
    Light* setSize(float size);
    Light* setColor(int r, int g, int b);
    float getLight(int& r, int& g, int& b);
	void onStart() {};
	void onUpdate(int ticks) {};
	void onEnd() {};
};