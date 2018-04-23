#include <memory>
#include "Spikes.h"
#include "BoxCollider.h"
#include "GameManager.h"

Spikes::Spikes(Direction direction, Mode mode, float startX, float startY, float scale) : Obstacle(createSpriteInfo(), createColliderOffset(direction, scale), direction, mode, startX, startY, scale) {
    m_damagingRegion = GameManager::getInstance()->createGameObject<DamagingRegion>(false, 20, "Ghost.png", scale, scale, 0, false, startX, startY, 0);
}

std::shared_ptr<ComplexSpriteInfo> Spikes::createSpriteInfo()
{
	std::shared_ptr<ComplexSpriteInfo> spriteInfo = std::make_shared<ComplexSpriteInfo>();
    spriteInfo->addSprite("SpikesEnabled.png", "SpikesEnabled", 1, 1);
    spriteInfo->addSprite("SpikesDisabled.png", "SpikesDisabled", 1, 1);
	return spriteInfo;
}

void Spikes::setState(Mode mode)
{
	m_mode = mode;
	switch (m_mode)
	{
	case Obstacle::Enabled:
		changeSpriteSheet(Disabled);
		break;
	case Obstacle::Disabled:
        m_damagingRegion->clearHitList();
		changeSpriteSheet(Enabled);
		break;
	default:
		break;
	}
}