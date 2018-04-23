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

std::shared_ptr<ComplexSpriteInfo> Panel::generateComplexSpriteInfo(string image)
{
	std::shared_ptr<ComplexSpriteInfo> spriteInfo = std::make_shared<ComplexSpriteInfo>();
	spriteInfo->addSprite(image + "Blank.png", image + "Blank", 1, 1);
	spriteInfo->addSprite(image + ".png", image, 1, 1);
	return spriteInfo;
}

void Panel::setVisible(bool set)
{
	if (set)
		changeSpriteSheet(VISIBLE);
	else
		changeSpriteSheet(INVISIBLE);
}
