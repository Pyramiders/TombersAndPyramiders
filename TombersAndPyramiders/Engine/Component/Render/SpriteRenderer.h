#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "ISprite.h"

class SpriteRenderer : public Renderer
{
private:
	GLuint m_textureBufferID;
	Shader* m_activeShader;
	ISprite* m_activeSprite;

public:
	SpriteRenderer(GameObject* gameObject);
	void render();
	void setActiveShader(Shader* shader);
	void setActiveSprite(ISprite* sprite);
	Shader* getShader();
	ISprite* getSprite();
	~SpriteRenderer();
};
