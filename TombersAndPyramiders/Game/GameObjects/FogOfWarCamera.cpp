#include "FogOfWarCamera.h"
#include "SharedConstants.h"
#include "GameManager.h"
#include "SpriteRendererManager.h"
#include "HelperFunctions.h"
#include "Light.h"

void FogOfWarCamera::init()
{
	m_regularPass.init();
	m_fogOfWarPass.init();
}

inline float lerp(float t, float a, float b)
{
	return a * (1 - t) + b * t;
}

void FogOfWarCamera::updateFogOfWarMask()
{
	const int downscale = 16;
	const int gameWidth = SCREEN_WIDTH / downscale;
	const int gameHeight = SCREEN_HEIGHT / downscale;
	unsigned char bytes[gameWidth * gameHeight * 4] = { 0 };
	for(int i = 0; i < gameWidth * gameHeight * 4; i += 4) 
	{
		bytes[i + 3] = 235;
	}

	auto objectsInBounds = GameManager::getInstance()->getObjectsInBounds(getTransform()->getX(), getTransform()->getY(), getGameWidth(), getGameHeight());


	for(int i = 0; i < objectsInBounds.size(); i++)
	{
		auto lightComponent = objectsInBounds[i]->getComponent<Light>();
		if (lightComponent != nullptr) {
			int lightR = 0;
			int lightG = 0;
			int lightB = 0;
			float lightSize = lightComponent->getLight(lightR, lightG, lightB);

			float lightSizePixels = lightSize * getUnitSize() / downscale;

			auto lightTransform = objectsInBounds[i]->getTransform();
			if (isOnScreen(lightTransform)) {
				int screenX = gameWidth / 2.0 - ((getTransform()->getX() - lightTransform->getX()) * getUnitSize() / downscale);
				int screenY = gameHeight / 2.0f - ((getTransform()->getY() - lightTransform->getY()) * getUnitSize() / downscale);
				float dist = getTransform()->getDistance(lightTransform);
				
				float t = 1 - std::min( std::max( dist / (getGameHeight() / 2.0f), 0.0f ), 1.0f);
				unsigned char r = lightR;//lerp(t, 0.0f, lightR);
				unsigned char g = lightG;//lerp(t, 0.0f, lightG);
				unsigned char b = lightB;//lerp(t, 0.0f, lightB);
				unsigned char a = 120;//lerp(t, 255.0f, 0.0f);
				//if (t < 0.4f) {
				//	r = lerp((1 - t), r, 0.0f);
				//	g = lerp((1 - t), g, 0.0f);
				//	b = lerp((1 - t), b, 0.0f);
				//	a = lerp((1 - t), a, 235.0f);
				//}
				
				int lightRadiusPixels = lightSizePixels / 2.0f;
				
				for(int x = -lightRadiusPixels; x < lightRadiusPixels; x++ ) {
					for(int y = -lightRadiusPixels; y < lightRadiusPixels; y++) {
						int pos = ((screenY + y) * gameWidth + (screenX) + x) * 4;
						if (pos >= 0 && pos < gameWidth * gameHeight * 4 - 3) {
							int culmulativeDist = abs(x) + abs(y);
							double hyp = sqrt(x*x + y*y);
							if (hyp < lightRadiusPixels) {
								bytes[pos] = std::max(bytes[pos], r);
								bytes[pos + 1] = std::max(bytes[pos + 1], g);
								bytes[pos + 2] = std::max(bytes[pos + 2], b);
								bytes[pos + 3] = ((float)culmulativeDist / (float)lightRadiusPixels) * a;
							}
						}
					}
				}
	
			}
		}
	}

	SpriteRendererManager::getInstance()->generateTexture(gameWidth, gameHeight, bytes, &m_fogOfWarMask);
}

int testCounter = 0;
bool full = false;
void FogOfWarCamera::applyRenderFilters(SpriteRendererManager* rendererManager)
{
	ensureInit();
	updateFogOfWarMask();
	m_regularPass.bindFrameBuffer();
	rendererManager->renderPass();
	m_regularPass.unbindFrameBuffer();
	rendererManager->renderFogOfWar(m_fogOfWarMask, m_regularPass);
}