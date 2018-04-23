#pragma once

#include "SimpleSprite.h"
#include "WorldItem.h"
#include <memory>
#include "BaseItem.h"

//Instance/MovableCharacter
class WorldItem : public SimpleSprite
{
private:
	std::shared_ptr<BaseItem> m_item;
	bool m_popupActive;

public:
	WorldItem(std::shared_ptr<BaseItem> item, float x = 0.0f, float y = 0.0f);
	~WorldItem() {}

	std::shared_ptr<BaseItem> pickupItem(); //Destroys self

	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};
};