#include "SpriteRenderer.h"
#include "SpriteRendererManager.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject) : Renderer(gameObject)
{
	SpriteRendererManager::getInstance()->addSpriteForRendering(this); //.subscribe(gameObject.id, this); NOTE: Not subscribing/unsubscribing for now
	m_activeShader = Shader::getShader();
}

void SpriteRenderer::render()
{
	glBindTexture(GL_TEXTURE_2D, m_textureBufferID);
	glDrawArrays(GL_QUADS, 0, 4);
}

void SpriteRenderer::setActiveShader(Shader* shader)
{
	m_activeShader = shader;
}

Shader* SpriteRenderer::getShader()
{
	return m_activeShader;
}

void SpriteRenderer::setActiveSprite(ISprite* sprite)
{
	m_activeSprite = sprite;
}

ISprite* SpriteRenderer::getSprite()
{
	return m_activeSprite;
}

SpriteRenderer::~SpriteRenderer()
{
	SpriteRendererManager::getInstance()->removeSpriteFromRendering(this);
}
