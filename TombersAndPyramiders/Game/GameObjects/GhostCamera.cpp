#include "GhostCamera.h"
#include "SharedConstants.h"
#include "GameManager.h"
#include "SpriteRendererManager.h"
#include "HelperFunctions.h"
#include "Light.h"

void GhostCamera::init()
{
	m_regularPass.init();
}

void GhostCamera::applyRenderFilters(SpriteRendererManager* rendererManager)
{
	ensureInit();
	m_regularPass.bindFrameBuffer();
	rendererManager->renderPass();
	m_regularPass.unbindFrameBuffer();
	rendererManager->renderFBO(m_regularPass, Shader::getShader(SHADER_PP_GRAYSCALE));
}