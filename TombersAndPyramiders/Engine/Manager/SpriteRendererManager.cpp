#include "SpriteRendererManager.h"
#include <iostream>
#include <algorithm>
#include <condition_variable>
#include "SpriteSheet.h"
#include "Camera.h"
#include "GameManager.h"

/*
TODO:
* Fix the thread issue as it's now single threaded


*/

//Statics must be given definitions
SpriteRendererManager *SpriteRendererManager::s_instance;

std::mutex threadMutex;
std::condition_variable condition;

SpriteRendererManager *SpriteRendererManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new SpriteRendererManager();
	return s_instance;
}

/*void SpriteRendererManager::Subscribe(int id, SpriteRenderer* spriteRenderer) {
spriteRenderers[id] = spriteRenderer;
}

void SpriteRendererManager::UnSubscribe(int id) {
spriteRenderers.erase(id);
}*/



void SpriteRendererManager::onUpdate(int ticks)
{
	for (int i = 0; i < m_spritesToSubscribe.size(); i++) 
	{
		if (m_spritesToSubscribe[i] != nullptr)
		{
			m_activeSprites[m_spritesToSubscribe[i]->getGameObject()->getId()] = m_spritesToSubscribe[i]->shared_from_this();
		}
	}
	m_spritesToSubscribe.clear();

	prepareRenderingThread();
	//Load fboPlainPass
	//renderReadingStick.lock();

	Camera::getActiveCamera()->applyRenderFilters(this);

	SDL_GL_SwapWindow(m_mainWindow);

	//condition.notify_one();
	//renderReadingStick.unlock();
}

SDL_Window* SpriteRendererManager::getWindow()
{
	return m_mainWindow;
}

SpriteRendererManager::SpriteRendererManager()
{
	m_quadVertices = {
		-0.5f, -0.5f, 0.0f,  //BottomLeft
		0.5f, -0.5f, 0.0f,   //BottomRight
		0.5f, 0.5f, 0.0f,    //TopRight
		-0.5f, 0.5f, 0.0f    //TopLeft
	};

	m_textCoordinates = {
		0.0f, 0.0f, //BottomLeft
		1.0f, 0.0f, //BottomRight
		1.0f, 1.0f, //TopRight
		0.0f, 1.0f  //TopLeft
	};

	m_indices = {
		0, 1, 2, // First Triangle. BottomRight
		0, 2, 3  // Second Triangle. TopLeft
	};


	m_renderingThreadIsAlive = true;
	m_rendering = false;
	//renderingThread = std::thread(&SpriteRendererManager::PrepareRenderingThread, this);
	//renderingThread.detach();

	m_fboPlainPass = FrameBufferObject(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_fboBloomBrightness = FrameBufferObject(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_fboHorizontalGaussianBlur = FrameBufferObject(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_fboGaussianBlur = FrameBufferObject(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_fboBloomBlurBrightness = FrameBufferObject(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_fboAmbientLighting = FrameBufferObject(SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool SpriteRendererManager::setOpenGLAttributes()
{
	//All SDL_Gl_SetAttribute returns negative on fail, 0 on success. If result is zero, all succeeded
	int result = 0;
	//SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//OpenGL 3.3 using GLSL 330
	result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	result += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//Turn on double buffering with a 24bit Z buffer
	//You may need to change this to 16 or 32 for your system
	result += SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return result == 0;
}

void SpriteRendererManager::printSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}

void SpriteRendererManager::checkSDLError(int line)
{
	std::string error = SDL_GetError();
	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;
		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;
		SDL_ClearError();
	}
}

bool SpriteRendererManager::init()
{
	////Setup SDL
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	if (!setOpenGLAttributes())
	{
		return false;
	}

	// Create our window centered as an OpenGL window
	m_mainWindow = SDL_CreateWindow("Tombers and Pyramiders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!m_mainWindow)
	{
		std::cout << "Unable to create window\n";
		checkSDLError(__LINE__);
		return false;
	}

	// Create our opengl context and attach it to our window
	m_glContext = SDL_GL_CreateContext(m_mainWindow);

	// This makes our buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);

	////Setup glew
	glewExperimental = GL_TRUE;
	glewInit();

	////Setup OpenGL Viewport
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);

	////Setup VBO/VAO/EBO's. This is for the concept of sprite specifically where we assume it will all be quads (two triangles) to make a sprite
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenBuffers(1, &m_CBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_quadVertices), m_quadVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);
	//4 points cause quad, 8 points cause x/y/z/r/g/b/tx/ty
	//position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	//color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	//textture coordinate attribute
	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textCoordinates), m_textCoordinates.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
	glBindVertexArray(0); //Unbind VAO
	glEnable(GL_NORMALIZE);

	m_fboPlainPass.init();
	m_fboGaussianBlur.init();
	m_fboHorizontalGaussianBlur.init();
	m_fboBloomBrightness.init();
	m_fboBloomBlurBrightness.init();
	m_fboAmbientLighting.init();

	return true;
}

void SpriteRendererManager::cleanup()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	// Delete our OpengL context
	if (m_glContext != NULL)
	{
		SDL_GL_DeleteContext(m_glContext);
	}
	// Destroy our window
	if (m_mainWindow != NULL)
	{
		SDL_DestroyWindow(m_mainWindow);
	}
	// Shutdown SDL 2
	SDL_Quit();
}


GLuint SpriteRendererManager::generateTexture(int width, int height, unsigned char* rawBytes, GLuint* texture) 
{
	if (*texture != 0) {
		glDeleteTextures(1, texture);
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, static_cast<void*>(rawBytes));
	glGenerateMipmap(GL_TEXTURE_2D);
	const char *sdlError = SDL_GetError();
	GLenum glError = glGetError();
	if (strlen(sdlError) > 0)
	{
		std::cout << "SDL ERROR: " << sdlError << std::endl;
	}
	if (glError != GL_NO_ERROR)
	{
		std::cout << "GL ERROR: " << glError << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return *texture;
}

GLuint SpriteRendererManager::generateTexture(std::string textureFileName)
{

	if (m_cachedTextures.find(textureFileName) == m_cachedTextures.end() || true)
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		SDL_Surface *temp = IMG_Load(textureFileName.c_str());
		if (temp == nullptr)
		{
			GLenum errors = glGetError();
			const char *sdlErrors = SDL_GetError();
			std::cout << "ERROR::SPRITERENDERERMANAGER::FAILED TO READ FILE IN GENERATETEXTURE\n GLError: " << errors << " \nSDLErrors: " << sdlErrors << std::endl;
			return 0;
		}
		//If it crashes, make sure the .png is 32bit not 24bit so it supports RGBA not RGB
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp->w, temp->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	
		const char *sdlError = SDL_GetError();
		GLenum glError = glGetError();
		if (strlen(sdlError) > 0)
		{
			std::cout << sdlError << std::endl;
		}
		if (glError != GL_NO_ERROR)
		{
			std::cout << glError << std::endl;
		}
	
		SDL_FreeSurface(temp);
		glBindTexture(GL_TEXTURE_2D, 0);
		m_cachedTextures[textureFileName] = texture;
		return texture;
	} else {
		return m_cachedTextures[textureFileName];
	}
}


bool sortByZ(std::shared_ptr<SpriteRenderer> lhs, std::shared_ptr<SpriteRenderer> rhs)
{
	return lhs->getGameObject()->getTransform()->getZ() < rhs->getGameObject()->getTransform()->getZ();
}

void SpriteRendererManager::prepareRenderingThread()
{
	if (m_activeSprites.size() > 0)
	{
		GLuint lastShaderUnset = 1000000;

		//while (isBeingCollected);
		//std::unique_lock<std::mutex> lock(threadMutex);

		//while (renderingThreadIsAlive)
		//{
		//condition.wait(lock);
		//renderReadingStick.lock();
		m_renderingGroups.clear();
		GLuint lastShader = lastShaderUnset;
		RenderingShaderGroup rg;

		std::shared_ptr<Camera> camera = Camera::getActiveCamera();

		std::vector<std::shared_ptr<SpriteRenderer>> renderers;

		//##Have Culled Objects. Find Ones To Render
		auto objectsInBounds = GameManager::getInstance()->getObjectsInBounds(camera->getTransform()->getX(), camera->getTransform()->getY(), getGameWidth(), getGameHeight());
		for (size_t i = 0; i < objectsInBounds.size(); i++)
		{
			if (objectsInBounds[i] == nullptr || objectsInBounds[i] == NULL)
			{
				continue;
			}
			if (m_activeSprites.find(objectsInBounds[i]->getId()) == m_activeSprites.end())
			{
				continue; //This game object is not one we're supposed to render either way
			}
			std::shared_ptr<SpriteRenderer> spriteRenderer = m_activeSprites[objectsInBounds[i]->getId()]; //objectsInBounds[i]->getComponent<SpriteRenderer>() also misculls so it is the getObjectsInBounds call itself
			if (spriteRenderer == nullptr)
			{
				continue;
			}
			renderers.push_back(spriteRenderer);
		}

		//##Have Renderers. Sort Them
		std::stable_sort(renderers.begin(), renderers.end(), sortByZ);

		//##Have Sorted Renderers. Prepare Rendering Info Objects
		for (size_t i = 0; i < renderers.size(); i++) {
			std::shared_ptr<SpriteRenderer> spriteRenderer = renderers[i];

			Transform* transform = spriteRenderer->getGameObject()->getTransform();
			
			RenderingObject ro;

			Shader *shader = spriteRenderer->getShader();
			if (shader == nullptr)
			{
				continue;
			}
			GLuint roShader = shader->program;
			ro.sprite = spriteRenderer->getSprite();

			if (lastShader == lastShaderUnset)
			{
				lastShader = roShader;
				rg.shaderProgram = roShader;
				rg.shaderID = shader->getID();
			}

			if (roShader != lastShader)
			{
				m_renderingGroups.push_back(rg);
				lastShader = roShader;
				rg = RenderingShaderGroup();
				rg.shaderProgram = roShader;
				rg.shaderID = shader->getID();
			}

			//Pass in transform
			ro.transform = transform;

			ro.spriteRenderer = spriteRenderer;

			if (ro.isValid())
			{
				rg.children.push_back(ro);
			}
		}
		m_renderingGroups.push_back(rg);
	}

	//renderReadingStick.unlock();
//}
}

void SpriteRendererManager::renderShadowPass(float xSourceDirection, float ySourceDirection, float shadowStrength)
{
	//Bind vertex array
	glBindVertexArray(m_VAO);

	for (size_t i = 0; i < m_renderingGroups.size(); i++)
	{
		RenderingShaderGroup rg = m_renderingGroups[i];
		Shader* shader = rg.shaderID == SHADER_SPRITESHEET ? Shader::getShader(SHADER_SHADOW_SPRITESHEET) : Shader::getShader(SHADER_SHADOW_DEFAULT);

		glUseProgram(shader->program);

		GLint lightPoint = glGetUniformLocation(shader->program, "lightPoint");
		glUniform2f(lightPoint, xSourceDirection, ySourceDirection);

		GLint shadowsStr = glGetUniformLocation(shader->program, "shadowStrength");
		glUniform1f(shadowsStr, shadowStrength);

		//Pass in Transform
		GLint transformLocation = glGetUniformLocation(shader->program, "transform");
		//Pass in aspect ratio
		GLint aspectRatioLocation = glGetUniformLocation(shader->program, "aspectRatio");
		//Pass in texture
		glActiveTexture(GL_TEXTURE0);
		GLint ourTextureLocation = glGetUniformLocation(shader->program, "ourTexture1");
		glUniform1i(ourTextureLocation, 0);

		//(Optional) For SpriteSheets only
		GLint spriteSheetLocation;
		if (rg.shaderID == SHADER_SPRITESHEET)
		{
			spriteSheetLocation = glGetUniformLocation(shader->program, "texData");
		}

		for (size_t j = 0; j < rg.children.size(); j++)
		{
			RenderingObject ro = rg.children[j];

			if (!ro.isValid())
			{
				continue;
			}

			if (ro.spriteRenderer->getLayer() != RENDER_LAYER_SHADOWABLE)
			{
				continue;
			}

			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, *(ro.transform));

			glUniform1f(aspectRatioLocation, ASPECT_RATIO);

			if (ro.sprite == nullptr)
			{
				continue;
			}

			glBindTexture(GL_TEXTURE_2D, ro.sprite->getTextureBufferID());

			if (rg.shaderID == SHADER_SPRITESHEET)
			{
				SpriteSheet spriteSheet = *((SpriteSheet *)ro.sprite.get());
				if (spriteSheet.getColumnCount() > 1000)
				{
					int hit = 0;
				}
				glUniform3i(spriteSheetLocation, spriteSheet.getColumnCount(), spriteSheet.getRowCount(), spriteSheet.getCurrentIndex());
			}

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}

void SpriteRendererManager::renderPass(int layerToRender, bool clearFirst)
{
	if (clearFirst)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	//Bind vertex array
	glBindVertexArray(m_VAO);

	for (size_t i = 0; i < m_renderingGroups.size(); i++)
	{
		RenderingShaderGroup rg = m_renderingGroups[i];
		glUseProgram(rg.shaderProgram);

		//Pass in Transform
		GLint transformLocation = glGetUniformLocation(rg.shaderProgram, "transform");
		//Pass in aspect ratio
		GLint aspectRatioLocation = glGetUniformLocation(rg.shaderProgram, "aspectRatio");
		//Pass in texture
		glActiveTexture(GL_TEXTURE0);
		GLint ourTextureLocation = glGetUniformLocation(rg.shaderProgram, "ourTexture1");
		glUniform1i(ourTextureLocation, 0);

		//(Optional) For SpriteSheets only
		GLint spriteSheetLocation;
		if (rg.shaderID == SHADER_SPRITESHEET)
		{
			spriteSheetLocation = glGetUniformLocation(rg.shaderProgram, "texData");
		}

		for (size_t j = 0; j < rg.children.size(); j++)
		{
			RenderingObject ro = rg.children[j];

			if (layerToRender != RENDER_LAYER_ALL && layerToRender != ro.spriteRenderer->getLayer())
			{
				continue;
			}

			if (ro.isValid())
			{
				glUniformMatrix4fv(transformLocation, 1, GL_FALSE, *(ro.transform));
			}
			else
			{
				continue;
			}

			glUniform1f(aspectRatioLocation, ASPECT_RATIO);

			glBindTexture(GL_TEXTURE_2D, ro.sprite->getTextureBufferID());

			if (rg.shaderID == SHADER_SPRITESHEET)
			{
				SpriteSheet* spriteSheet = ((SpriteSheet *)ro.sprite.get());
				if (spriteSheet != nullptr)
				{
					if (spriteSheet->getColumnCount() > 1000)
					{
						int hit = 0;
					}
					glUniform3i(spriteSheetLocation, spriteSheet->getColumnCount(), spriteSheet->getRowCount(), spriteSheet->getCurrentIndex());
				}
				else {
					int hit = 1;
				}
			}

			//Draw
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}

void SpriteRendererManager::renderFBO(FrameBufferObject object, Shader* shader, FrameBufferObject* toFbo)
{
	if (toFbo != nullptr)
	{
		toFbo->bindFrameBuffer();
	}
	shader->use();
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GLint ourTextureLocation = glGetUniformLocation(shader->program, "fboTexture");
	glUniform1i(ourTextureLocation, 0);
	//object.bindToRead();
	glBindTexture(GL_TEXTURE_2D, object.getTexture());
	//object.unbindFrameBuffer();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//Render FBO object with given shader
	if (toFbo != nullptr)
	{
		toFbo->unbindFrameBuffer();
	}
}

void SpriteRendererManager::renderGaussianBlur(FrameBufferObject fboToBlur, FrameBufferObject* toFbo)
{
	//Render fboToBlur with gaussianblur
	renderFBO(fboToBlur, Shader::getShader(SHADER_PP_HORIZONTALBLUR), &m_fboHorizontalGaussianBlur);
	renderFBO(m_fboHorizontalGaussianBlur, Shader::getShader(SHADER_PP_VERTICALBLUR), toFbo);
}

void SpriteRendererManager::renderFogOfWar(GLuint fogOfWarMask, FrameBufferObject gameRendering, FrameBufferObject* toFbo) 
{
	if (toFbo != nullptr)
	{
		toFbo->bindFrameBuffer();
	}
	Shader::getShader(SHADER_PP_FOGOFWAR)->use(); //
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(56.0f / 255.0f, 38.0f / 255.0f, 24.0f / 255.0f, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GLint ourTextureLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_FOGOFWAR)->program, "fogOfWarMask");
	glUniform1i(ourTextureLocation, 0);
	ourTextureLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_FOGOFWAR)->program, "gameRendering");
	glUniform1i(ourTextureLocation, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fogOfWarMask);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gameRendering.getTexture());
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//Render FBO object with given shader
	if (toFbo != nullptr)
	{
		toFbo->unbindFrameBuffer();
	}
}

void SpriteRendererManager::renderBloom(FrameBufferObject fboToBloom, FrameBufferObject* toFbo)
{
	renderFBO(m_fboPlainPass, Shader::getShader(SHADER_PP_EXTRACTLIGHT), &m_fboBloomBrightness);
	renderGaussianBlur(m_fboBloomBrightness, &m_fboBloomBlurBrightness); //Gaussian-Blur the light source
	GLint ourTextureLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_BLOOMCOMBINE)->program, "highlightTexture");
	glUniform1i(ourTextureLocation, 1);
	glActiveTexture(GL_TEXTURE1);
	//fboBloomBlurBrightness.bindToRead();
	glBindTexture(GL_TEXTURE_2D, m_fboBloomBlurBrightness.getTexture());
	//fboBloomBlurBrightness.unbindFrameBuffer();
	renderFBO(fboToBloom, Shader::getShader(SHADER_PP_BLOOMCOMBINE), toFbo);
}

void SpriteRendererManager::renderAmbientColor(FrameBufferObject fboToColor, float r, float g, float b, float a, FrameBufferObject* toFbo)
{
	if (toFbo != nullptr)
	{
		toFbo->bindFrameBuffer();
	}

	Shader::getShader(SHADER_PP_AMBIENTCOLOR)->use();
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint directionLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_AMBIENTCOLOR)->program, "ambientColor");
	glUniform4f(directionLocation, r, g, b, a);

	glActiveTexture(GL_TEXTURE0);
	GLint ourTextureLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_AMBIENTCOLOR)->program, "fboTexture");
	glUniform1i(ourTextureLocation, 0);
	glBindTexture(GL_TEXTURE_2D, fboToColor.getTexture());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	if (toFbo != nullptr)
	{
		toFbo->unbindFrameBuffer();
	}
}

void SpriteRendererManager::renderDirectionalBloom(FrameBufferObject fboToBloom, float xSourceDirection, float ySourceDirection, float bloomIntensity, FrameBufferObject* toFbo)
{
	//##From: fboTobloom To::fboBloomBrightness
	m_fboBloomBrightness.bindFrameBuffer();
	Shader::getShader(SHADER_PP_EXTRACTLIGHTDIRECTIONAL)->use();
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint directionLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_EXTRACTLIGHTDIRECTIONAL)->program, "bloomDirection");
	glUniform2f(directionLocation, xSourceDirection, ySourceDirection);

	glActiveTexture(GL_TEXTURE0);
	GLint ourTextureLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_EXTRACTLIGHTDIRECTIONAL)->program, "fboTexture");
	glUniform1i(ourTextureLocation, 0);
	glBindTexture(GL_TEXTURE_2D, fboToBloom.getTexture());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_fboBloomBrightness.unbindFrameBuffer();
	//###########

	//##From::fboBloomBrightness To::fboBloomBlurBrightness##
	renderGaussianBlur(m_fboBloomBrightness, &m_fboBloomBlurBrightness); //Gaussian-Blur the light source
	//###########

	//##From::fboBloomBlurBrightness	To:toFBO##
	if (toFbo != nullptr)
	{
		toFbo->bindFrameBuffer();
	}
	Shader::getShader(SHADER_PP_BLOOMCOMBINE)->use();
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint bloomIntensityLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_BLOOMCOMBINE)->program, "bloomIntensity");
	glUniform1f(bloomIntensityLocation, bloomIntensity);

	glActiveTexture(GL_TEXTURE0);
	ourTextureLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_BLOOMCOMBINE)->program, "fboTexture");
	glUniform1i(ourTextureLocation, 0);
	glBindTexture(GL_TEXTURE_2D, fboToBloom.getTexture());

	glActiveTexture(GL_TEXTURE1);
	ourTextureLocation = glGetUniformLocation(Shader::getShader(SHADER_PP_BLOOMCOMBINE)->program, "highlightTexture");
	glUniform1i(ourTextureLocation, 1);
	glBindTexture(GL_TEXTURE_2D, m_fboBloomBlurBrightness.getTexture());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	if (toFbo != nullptr)
	{
		toFbo->unbindFrameBuffer();
	}
	//#######
}


void SpriteRendererManager::renderFullLighting(FrameBufferObject fboToEffect, FrameBufferObject bloomBlurredLight, FrameBufferObject shadow, FrameBufferObject moodLighting, FrameBufferObject* toFbo)
{
	//fboToEffect has the regular drawn world
	//bloomBlurredLight = RenderDirectionalBloom() directional bloom data
	//shadow = RenderShadow() shadow data
	//moodLighting = RenderAmbientLighting() overall evenly lit data

	//Apply Shadow to fboToEffect
	//Apply MoodLighting to fboToEffect+Shadow
	//Apply Bloom to fboToEffect+MoodLighting+Shadow
}

void SpriteRendererManager::applyEndProcessing(FrameBufferObject mainTexture, FrameBufferObject postProcessingOverlay, FrameBufferObject* toFbo)
{
	//Draw mainTexture with postProcessingOverlay overlayed
}

void SpriteRendererManager::addSpriteForRendering(SpriteRenderer* sprite)
{
	if (sprite != nullptr && sprite != nullptr && sprite->getGameObject() != nullptr && sprite->getGameObject() != NULL)
	{
		m_spritesToSubscribe.push_back(sprite); //Have to lazy load it into a spritesToAdd list because sprite->getGameObject->getId() is not set when SpriteRenderer's constructor is called
	}
}

void SpriteRendererManager::disableRenderingLayer(int layer)
{
	m_disabledLayers.insert(layer);
}

void SpriteRendererManager::enableRenderingLayer(int layer)
{
	m_disabledLayers.erase(layer);
}

void SpriteRendererManager::enableAllRenderingLayers()
{
	m_disabledLayers.clear();
}

bool SpriteRendererManager::isRenderingLayerEnabled(int layer)
{
	return m_disabledLayers.find(layer) == m_disabledLayers.end();
}

void SpriteRendererManager::removeSpriteFromRendering(int objectID)
{
	m_activeSprites[objectID] = nullptr;
}

void SpriteRendererManager::purge()
{
	m_activeSprites.clear();
}