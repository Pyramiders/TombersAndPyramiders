#include "GhostCharacter.h"
#include "GhostController.h"


const float GhostCharacter::MIN_POSSESS_SIZE = 1.5f;
const float GhostCharacter::MAX_POSSESS_SIZE = 2.5f;
const float GhostCharacter::SIZE_CHANGE_RATE = 0.05f;

//GhostCharacter GameObject which contains a GhostController and Pilot and has two moves, Ghost and Possessing modes
GhostCharacter::GhostCharacter(BasePilot* pilot) : ComplexSprite(createSpriteInfo(), 0, 0, 1.0f, 1.0f, nullptr, 16)
{
	addComponent<GhostController>(this, pilot);
	addComponent<AudioListener>(this);
	m_mode = ghost;
}

std::shared_ptr<ComplexSpriteInfo> GhostCharacter::createSpriteInfo()
{
	auto spriteInfo = std::make_shared<ComplexSpriteInfo>();

	spriteInfo->addSprite("ghostIdle.png", "ghostIdle", 8, 1);
	spriteInfo->addSprite("ghostPossessing.png", "ghostPossessing", 8, 1);

	return spriteInfo;
}

void GhostCharacter::setMode(Mode mode)
{
	m_mode = mode;
	switch (m_mode)
	{
	//Ghost == Default
	case ghost:
		changeSpriteSheet(0);
		getTransform()->setScale(1.0f);
		getTransform()->setZ(1.0f);
		break;
	//Possessing == Play animation, growing and shrinking the effect
	case possessing:
		changeSpriteSheet(1);
		getTransform()->setScale(MIN_POSSESS_SIZE);
		m_sizeChange = SIZE_CHANGE_RATE;
		getTransform()->setZ(-1.0f);
		break;
	}
}

GhostCharacter::Mode GhostCharacter::getMode()
{
	return m_mode;
}

void GhostCharacter::onUpdate(int ticks)
{
	updateFrames(ticks);
	if (m_mode == possessing)
	{
		float size = getTransform()->getScale();
		if (m_sizeChange > 0 && size >= MAX_POSSESS_SIZE) //Growing + MaxSize == Start Shrinking
		{
			m_sizeChange = -SIZE_CHANGE_RATE;
		}
		else if (m_sizeChange < 0 && size <= MIN_POSSESS_SIZE) //Shrinking + MinSize == Start Growing
		{
			m_sizeChange = SIZE_CHANGE_RATE;
		}
		getTransform()->setScale(size + m_sizeChange);
	}
}

void GhostCharacter::onStart()
{
	std::cout << "GhostCharacter::onStart" << std::endl;
}

GhostCharacter::~GhostCharacter()
{

}