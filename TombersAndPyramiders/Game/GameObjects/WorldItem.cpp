#include "WorldItem.h"

WorldItem::WorldItem(std::shared_ptr<BaseItem> item, float x, float y) : SimpleSprite(item->getItemIcon(), x, y)
{
	m_item = item;
	//Add component: BoxCollider and detect collision
}

std::shared_ptr<BaseItem> WorldItem::pickupItem()
{
	destroy(getId());
	return m_item;
}

