#include "SpinningEffect.h"


SpinningEffect::SpinningEffect() : ComplexSprite(createSpriteInfo(), 0, 0, 1.0f, 2.0f)
{
}

std::shared_ptr<ComplexSpriteInfo> SpinningEffect::createSpriteInfo()
{
	auto spriteInfo = std::make_shared<ComplexSpriteInfo>();
	spriteInfo->addSprite("ghostPossessing.png", "Spin", 8, 1);
	spriteInfo->addAnimation("Spin", "Spinning", 0, 7);

	return spriteInfo;
}

void SpinningEffect::onStart()
{
	changeAnimation("Spinning");
    getTransform()->setZ(999);
}

void SpinningEffect::onUpdate(int ticks)
{
    if (getTransform()->getScale() < 10.0f) {
        getTransform()->setScale(getTransform()->getScale() + 0.1f);
    }
    getTransform()->addRotation(36.0f);
    std::cout << "Spinning " << getTransform()->getScale() << " " << std::endl;
}

SpinningEffect::~SpinningEffect()
{
	
}
