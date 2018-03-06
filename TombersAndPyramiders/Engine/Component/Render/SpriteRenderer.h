#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "ISprite.h"
#include <memory>

class SpriteRenderer : public Renderer, public std::enable_shared_from_this<SpriteRenderer>
{
private:
	GLuint m_textureBufferID;
	Shader* m_activeShader;
	std::shared_ptr<ISprite> m_activeSprite;

public:
	SpriteRenderer(GameObject* gameObject);
	void render();
	void setActiveShader(Shader* shader);
	void setActiveSprite(std::shared_ptr<ISprite> sprite);
	Shader* getShader();
	std::shared_ptr<ISprite> getSprite();
	~SpriteRenderer();
};
