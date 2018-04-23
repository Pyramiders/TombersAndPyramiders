#include "PositionBasedPopup.h"

PositionBasedPopup::PositionBasedPopup(float x, float y, float maxDistance, std::shared_ptr<GameObject> dependant, std::string imageName) : SimpleSprite(imageName, x, y, 1000000, 6.0f)
{
	m_maxDistance = maxDistance;
	m_dependant = dependant;
}

PositionBasedPopup::~PositionBasedPopup()
{

}

void PositionBasedPopup::onStart()
{

}

void PositionBasedPopup::onUpdate(int ticks)
{
	if (m_dependant != nullptr)
	{
		if (getTransform()->getDistance(m_dependant->getTransform()) > m_maxDistance)
		{
			destroy(getId());
		}
	}
	else
	{
		destroy(getId());
	}
}