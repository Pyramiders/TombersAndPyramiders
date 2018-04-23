#include "AnimatedItem.h"

AnimatedItem::AnimatedItem(std::shared_ptr<BaseItem> derivedFrom) : ComplexSprite(derivedFrom->spriteInfo, 0, 0)
{
	m_derivedItem = derivedFrom;
}

AnimatedItem::~AnimatedItem()
{
}
