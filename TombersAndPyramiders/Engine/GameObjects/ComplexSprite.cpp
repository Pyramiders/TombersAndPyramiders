#include "ComplexSprite.h"
#include "SpriteRendererManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Shader.h"
#include "HelperFunctions.h"

ComplexSprite::ComplexSprite(ComplexSpriteinfo* info, float x, float y, float z, float scale, Shader* nonDefaultShader, int framesPerSecond) : GameObject(false)
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this);
	spriteRenderer->setActiveShader(Shader::getShader(SHADER_SPRITESHEET));

	for (int i = 0; i != info->getSpriteCount(); i++)
	{
		std::string totalPath("Game/Assets/Sprites/" + info->getFilePath(i));
		GLuint texture = SpriteRendererManager::getInstance()->generateTexture(BuildPath((char*)totalPath.c_str()));
		int columns = info->getColumnCount(i);
		int rows = info->getRowCount(i);
		m_sprites.push_back(new SpriteSheet(texture, columns, rows));
	}

	if (nonDefaultShader != nullptr)
	{
		m_shader = nonDefaultShader;
		spriteRenderer->setActiveShader(m_shader);
	}

	m_currentSpriteSheet = 0;
	spriteRenderer->setActiveSprite(m_sprites[m_currentSpriteSheet]);

	Transform* transform = getTransform();
	transform->setPosition(x, y, z);
	transform->setScale(scale);
	addComponent<SpriteRenderer*>(spriteRenderer);
	m_framesTilReturn = -1;
	this->m_framesPerSecond = framesPerSecond;

}

ComplexSprite::~ComplexSprite()
{
	for (int i = 0; i < m_sprites.size(); i++)
	{
		delete(m_sprites[i]);
		m_sprites[i] = NULL;
	}
	m_sprites.clear();
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
	m_sprites[m_currentSpriteSheet]->nextIndex();
	if (m_framesTilReturn > -1)
	{
		if (--m_framesTilReturn == 0)
		{
			changeSprite(m_spriteToReturnTo);
			m_framesTilReturn = -1;
		}
	}
}

void ComplexSprite::changeSprite(int spriteIndexInComplexInfo)
{
	if (spriteIndexInComplexInfo != m_currentSpriteSheet && m_currentSpriteSheet >= 0)
	{
		m_sprites[m_currentSpriteSheet]->resetIndex();
		m_currentSpriteSheet = spriteIndexInComplexInfo;
		getComponent<SpriteRenderer*>()->setActiveSprite(m_sprites[spriteIndexInComplexInfo]);
	}
}

int ComplexSprite::getCurrentSprite()
{
	return m_currentSpriteSheet;
}

void ComplexSprite::changeSprite(int spriteIndexInComplexInfo, int returnSprite)
{
	if (m_sprites.size() > 0)
	{
		changeSprite(spriteIndexInComplexInfo);
		m_spriteToReturnTo = returnSprite;
		m_framesTilReturn = m_sprites[returnSprite]->getColumnCount() * m_sprites[returnSprite]->getRowCount();
	}
}