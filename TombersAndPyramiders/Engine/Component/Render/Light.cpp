#include "Light.h"

Light::Light(GameObject* gameObject) : Component(gameObject) 
{
    m_size = 1;
    m_red = 255;
    m_green = 255;
    m_blue = 255;
}

Light* Light::setColor(int red, int green, int blue) 
{
    m_red = red;
    m_green = green;
    m_blue = blue;
    return this;
}

Light* Light::setSize(float size) 
{
    m_size = size;
    return this;
}

float Light::getLight(int& r, int& g, int& b) 
{
    r = m_red;
    g = m_green;
    b = m_blue;
    return m_size;
}