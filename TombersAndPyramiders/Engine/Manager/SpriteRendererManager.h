#pragma once

#include <map> ////
#include "GLHeaders.h"
#include <stdio.h>
#include <string>
#define GL3_PROTOTYPES 1
#include <iostream>
#include "SharedConstants.h"
#include <vector>
#include <array>
#include "SpriteRenderer.h"
#include "Transform.h"
#include <unordered_set>
#include <thread>
#include <mutex>
#include "FrameBufferObject.h"
#include "UserDefinedRenderLayers.h"
#include <memory>
#include <map>

#define SHADER_TYPE_DEFAULT 0
#define SHADER_TYPE_PIXEL 1
#define SHADER_TYPE_SPRITESHEET 2

struct RenderingObject
{
	std::shared_ptr<ISprite> sprite;
	Transform* transform;
	std::shared_ptr<SpriteRenderer> spriteRenderer;

	bool isValid()
	{
		if (spriteRenderer == NULL || spriteRenderer == nullptr || transform == NULL || transform == nullptr)
		{
			return false;
		}
		return true;
	}
};

struct RenderingTextureCoordinateGroup
{

};

struct RenderingShaderGroup
{
	int shaderID;
	GLuint shaderProgram;
	std::vector<RenderingObject> children;
	~RenderingShaderGroup()
	{
		children.clear();
	}
};

class SpriteRendererManager
{
private:
	//Singleton variables
	static SpriteRendererManager *s_instance;
	std::map<int, std::shared_ptr<SpriteRenderer>> m_activeSprites;
	std::vector<SpriteRenderer*> m_spritesToSubscribe;
	std::unordered_set<int> m_disabledLayers;
	std::thread m_renderingThread;
	std::mutex m_renderTalkingStick;
	std::mutex m_renderReadingStick;
	std::vector<RenderingShaderGroup> m_renderingGroups;
	bool m_renderingThreadIsAlive;
	bool m_rendering;
	FrameBufferObject m_fboPlainPass, m_fboHorizontalGaussianBlur, m_fboGaussianBlur, m_fboBloomBrightness, m_fboBloomBlurBrightness, m_fboAmbientLighting;
	map<std::string, GLuint> m_cachedTextures;

	//Rendering variables
	SDL_Window* m_mainWindow = NULL;
	SDL_GLContext m_glContext = NULL;
	std::array<GLfloat, 12> m_quadVertices;
	std::array<GLfloat, 8> m_textCoordinates;
	std::array<GLuint, 6> m_indices;
	GLuint m_VBO, m_VAO, m_EBO, m_CBO; //VertexBufferObject, VertexArrayObject, ElementsBufferObject, CoordinateBufferObject
	GLuint m_ppVAO;

	//Rendering methods
	bool setOpenGLAttributes();
	void printSDL_GL_Attributes();
	void checkSDLError(int line);
	void prepareRenderingThread();


public:
	static SpriteRendererManager* getInstance();

	//void Subscribe(int id, SpriteRenderer* spriteRenderer);
	//void UnSubscribe(int id);
	void onUpdate(int ticks);

	SDL_Window* getWindow();

	SpriteRendererManager();
	bool init();
	void cleanup();
	void render();
	GLuint generateTexture(std::string textureFileName);
	GLuint generateTexture(int width, int height, unsigned char* rawBytes, GLuint* texture);
	void addSpriteForRendering(SpriteRenderer* sprite);

	void disableRenderingLayer(int layer);
	void enableRenderingLayer(int layer);
	void enableAllRenderingLayers();
	bool isRenderingLayerEnabled(int layer);
	void removeSpriteFromRendering(int objectID);
	void purge();

	/////RENDERING METHODS: Maybe extract to a base "RenderContext" class to pass to the Camera
	void renderShadowPass(float xSourceDirection, float ySourceDirection, float shadowStrength);
	void renderPass(int layer = 0, bool clearFirst = true);
	void renderFBO(FrameBufferObject fboToRender, Shader* shader, FrameBufferObject* toFbo = nullptr); //Default "FBOShader" type assumes it takes a texture to draw

	void renderFogOfWar(GLuint fogOfWarMask, FrameBufferObject gameRendering, FrameBufferObject* toFbo = nullptr);
	void renderGaussianBlur(FrameBufferObject fboToBlur, FrameBufferObject* toFbo = nullptr); //Blurs then draws
	void renderBloom(FrameBufferObject fboToBloom, FrameBufferObject* toFbo = nullptr); //Takes input, extracts light, stores that, blurrs, stores that
	void renderDirectionalBloom(FrameBufferObject fboToBloom, float xSourceDirection, float ySourceDirection, float bloomIntensity, FrameBufferObject* toFbo = nullptr); //Takes input, extracts light, stores that, blurrs, stores that
	void applyEndProcessing(FrameBufferObject mainTexture, FrameBufferObject postProcessingOverlay, FrameBufferObject* toFbo = nullptr);
	void renderAmbientColor(FrameBufferObject fboToColor, float r, float g, float b, float a, FrameBufferObject* toFbo = nullptr);
	void renderFullLighting(FrameBufferObject fboToEffect, FrameBufferObject bloomBlurredLight, FrameBufferObject shadow, FrameBufferObject moodLighting, FrameBufferObject* toFbo = nullptr);
};