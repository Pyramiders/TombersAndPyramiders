#include "SimpleSprite.h"
#include "SpriteRendererManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Shader.h"
#include "HelperFunctions.h"

SimpleSprite::SimpleSprite(std::string path, float x, float y, float z, float scale, Shader* nonDefaultShader) : GameObject()
{
	std::string totalPath("Game/Assets/Sprites/" + path);
	GLuint titleTexture = SpriteRendererManager::getInstance()->generateTexture(BuildPath((char*)totalPath.c_str()));
	m_sprite = std::make_shared<Sprite>(titleTexture);
	std::shared_ptr<SpriteRenderer> spriteRenderer = addComponent<SpriteRenderer>(this);
	Transform* transform = getTransform();
	if (nonDefaultShader != nullptr)
	{
		m_shader = nonDefaultShader;
		spriteRenderer->setActiveShader(m_shader);
	}
	spriteRenderer->setActiveSprite(m_sprite);
	transform->setPosition(x, y, z);
	transform->setScale(scale);
}

/*SimpleSprite::~SimpleSprite() {
	if (sprite != nullptr) {
	   delete(sprite);
	}
}*/