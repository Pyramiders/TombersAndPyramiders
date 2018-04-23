#include "ComplexSprite.h"
#include "SpriteRendererManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Shader.h"
#include "HelperFunctions.h"

ComplexSprite::ComplexSprite(std::shared_ptr<ComplexSpriteInfo> info, float x, float y, float z, float scale, Shader* nonDefaultShader, int framesPerSecond) : GameObject()
{
	m_spriteInfo = info;

	std::shared_ptr<SpriteRenderer> spriteRenderer = addComponent<SpriteRenderer>(this);
	spriteRenderer->setActiveShader(Shader::getShader(SHADER_SPRITESHEET));

	for (int i = 0; i != info->getSpriteCount(); i++)
	{
		std::string totalPath("Game/Assets/Sprites/" + info->getFilePath(i));
		GLuint texture = SpriteRendererManager::getInstance()->generateTexture(BuildPath((char*)totalPath.c_str()));
		int columns = info->getColumnCount(i);
		int rows = info->getRowCount(i);
		m_spriteSheets.push_back(std::make_shared<SpriteSheet>(texture, columns, rows));
	}

	if (nonDefaultShader != nullptr)
	{
		m_shader = nonDefaultShader;
		spriteRenderer->setActiveShader(m_shader);
	}

	m_currentSpriteSheetIndex = 0;
	spriteRenderer->setActiveSprite(m_spriteSheets[m_currentSpriteSheetIndex]);

	Transform* transform = getTransform();
	transform->setPosition(x, y, z);
	transform->setScale(scale);

	m_currentAnimationIndex = -1;
	m_framesTilReturn = -1;
	this->m_framesPerSecond = framesPerSecond;
}

void ComplexSprite::setFPS(int fps)
{
	m_framesPerSecond = fps;
}

void ComplexSprite::updateFrames(float delta)
{
	int timeSince = m_timeAlive - m_lastFrame;
	float secondsPerFrame = 1.0f / (float)m_framesPerSecond * 1000;
	if (timeSince > secondsPerFrame)
	{
		m_lastFrame = m_timeAlive;
		nextFrame();
	}
	m_timeAlive += delta;
}

void ComplexSprite::nextFrame()
{
	m_spriteSheets[m_currentSpriteSheetIndex]->nextIndex();
	if (m_framesTilReturn > -1)
	{
		if (--m_framesTilReturn == 0)
		{
			if (m_spriteSheetToReturnTo != -1 && m_animationtoReturnTo != -1)
			{
				changeSpriteSheet(m_spriteSheetToReturnTo);
				changeAnimation(m_animationtoReturnTo);
			}
			else if (m_spriteSheetToReturnTo != -1)
			{
				changeSpriteSheet(m_spriteSheetToReturnTo);
			}
			else if (m_animationtoReturnTo != -1)
			{
				changeAnimation(m_animationtoReturnTo);
			}
			m_framesTilReturn = -1;
		}
	}
}

bool ComplexSprite::changeSpriteSheet(int spriteIndexInComplexInfo)
{
	if (spriteIndexInComplexInfo < 0 || spriteIndexInComplexInfo > m_spriteSheets.size() - 1)
	{
		return false;
	}
	if (spriteIndexInComplexInfo != m_currentSpriteSheetIndex && m_currentSpriteSheetIndex >= 0)
	{
		m_spriteSheets[m_currentSpriteSheetIndex]->resetIndex();
		m_currentSpriteSheetIndex = spriteIndexInComplexInfo;
		getComponent<SpriteRenderer>()->setActiveSprite(m_spriteSheets[spriteIndexInComplexInfo]);
		m_currentAnimationIndex = -1;

		return true;
	}

	return false;
}

int ComplexSprite::getCurrentSpriteSheetIndex()
{
	return m_currentSpriteSheetIndex;
}

std::string ComplexSprite::getCurrentSpriteSheetName()
{
	return m_currentSpriteSheetName;
}

bool ComplexSprite::changeSpriteSheet(std::string spriteName)
{
	int index = m_spriteInfo->getSpriteIndex(spriteName);
	return changeSpriteSheet(index);
}

bool ComplexSprite::changeSpriteSheet(int spriteIndexInComplexInfo, int returnSprite)
{
	if (spriteIndexInComplexInfo < 0 || spriteIndexInComplexInfo > m_spriteSheets.size() - 1)
	{
		return false;
	}

	if (m_spriteSheets.size() > 0)
	{
		changeSpriteSheet(spriteIndexInComplexInfo);
		m_spriteSheetToReturnTo = returnSprite;
		m_framesTilReturn = m_spriteSheets[returnSprite]->getColumnCount() * m_spriteSheets[returnSprite]->getRowCount();
		m_currentAnimationIndex = -1;

		return true;
	}

	return false;
}

bool ComplexSprite::changeAnimation(std::string animationName, int animationIndexToReturnTo)
{
	// If an animation with that name already exists, return false.
	int animationIndex = m_spriteInfo->getAnimationIndex(m_currentSpriteSheetIndex, animationName);

	if (animationIndex != -1)
	{
		return changeAnimation(animationIndex, animationIndexToReturnTo);
	}

	return true;
}

bool ComplexSprite::changeAnimation(std::string animationName, std::string animationNameToReturnTo)
{
	int animationIndex = m_spriteInfo->getAnimationIndex(m_currentSpriteSheetIndex, animationNameToReturnTo);
	return changeAnimation(animationName, animationIndex);
}

bool ComplexSprite::changeAnimation(int animationIndex, int animationIndexToReturnTo)
{
	if (animationIndex == m_currentAnimationIndex)
	{
		return false;
	}

	if (animationIndex < 0 || animationIndex >= m_spriteInfo->m_animations[m_currentSpriteSheetIndex].size())
	{
		return false;
	}
	m_currentAnimationIndex = animationIndex;
	if (animationIndexToReturnTo != -1 && animationIndexToReturnTo >= 0 && animationIndexToReturnTo < m_spriteInfo->m_animations[m_currentSpriteSheetIndex].size())
	{
		m_animationtoReturnTo = animationIndexToReturnTo;
		int endFrame = m_spriteInfo->m_animations[m_currentSpriteSheetIndex][m_currentAnimationIndex].m_endFrameIndex;
		int startFrame = m_spriteInfo->m_animations[m_currentSpriteSheetIndex][m_currentAnimationIndex].m_startFrameIndex;

  		m_framesTilReturn = endFrame - startFrame;
	}

	updateSpriteSheetAnimation(m_currentAnimationIndex);
	return true;
}

void ComplexSprite::updateSpriteSheetAnimation(int animationIndex)
{
	int startFrame = m_spriteInfo->m_animations[m_currentSpriteSheetIndex][animationIndex].m_startFrameIndex;
	int endFrame = m_spriteInfo->m_animations[m_currentSpriteSheetIndex][animationIndex].m_endFrameIndex;

	m_spriteSheets[m_currentSpriteSheetIndex]->changeAnimation(startFrame, endFrame);
}