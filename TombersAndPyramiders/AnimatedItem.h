#pragma once
#include "ComplexSprite.h"
#include "BaseItem.h"

class AnimatedItem : public ComplexSprite
{
public:
	AnimatedItem(std::shared_ptr<BaseItem> derivedFrom);
	~AnimatedItem();

	std::shared_ptr<BaseItem> m_derivedItem;
};

