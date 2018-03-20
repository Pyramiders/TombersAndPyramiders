#include "Panel.h"

Panel::Panel(float x, float y, float width, float height, string image) : ComplexSprite(generateComplexSpriteInfo(image), x / 25, y / 25, 0, 20)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_image = image;
}

Panel::~Panel()
{

}

std::shared_ptr<ComplexSpriteinfo> Panel::generateComplexSpriteInfo(string image)
{
	std::shared_ptr<ComplexSpriteinfo> spriteInfo = std::make_shared<ComplexSpriteinfo>();
	spriteInfo->addInfo(image + "Blank.png", 1, 1);
	spriteInfo->addInfo(image + ".png", 1, 1);
	return spriteInfo;
}

void Panel::setVisible(bool set)
{
	if (set)
		changeSprite(VISIBLE);
	else
		changeSprite(INVISIBLE);
}
