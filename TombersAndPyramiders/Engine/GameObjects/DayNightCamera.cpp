#include "DayNightCamera.h"

int tempCounter = 0;
int tick = 0;
float sR, sG, sB, sA, sX, sY, sS, sBI;
float curR = 0.1f, curG = 0.1f, curB = 0.1f, curA = 0.5f;
float wantR = 0.1f, wantG = 0.1f, wantB = 0.1f, wantA = 0.5f;
float curX = -0.5f, curY = 0.5f;
float wantX = -0.5f, wantY = 0.5f;
float curS = 4.0f, wantS = 4.0f;
float bmFactor = 0.75f;
float wantBI = 0.135f * bmFactor, curBI = 0.135f * bmFactor;

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void DayNightCamera::init()
{
	m_regularPass.init();
	m_ambientLighting.init();
}

void DayNightCamera::applyRenderFilters(SpriteRendererManager* rendererManager)
{
	ensureInit();

	m_regularPass.bindFrameBuffer();//

	rendererManager->renderPass(RENDER_LAYER_BACKGROUND);
	rendererManager->renderShadowPass(curX, curY, curS);
	rendererManager->renderPass(RENDER_LAYER_SHADOWABLE, false);
	rendererManager->renderPass(RENDER_LAYER_FOREGROUND, false);

	m_regularPass.unbindFrameBuffer();//

	rendererManager->renderDirectionalBloom(m_regularPass, curX, curY, curBI, &m_ambientLighting);
	rendererManager->renderAmbientColor(m_ambientLighting, curR, curG, curB, curA);

	float t = tick / 480.0f; //

	curR = lerp(sR, wantR, t);
	curG = lerp(sG, wantG, t);
	curB = lerp(sB, wantB, t);
	curA = lerp(sA, wantA, t);
	curX = lerp(sX, wantX, t);
	curY = lerp(sY, wantY, t);
	curS = lerp(sS, wantS, t);
	curBI = lerp(sBI, wantBI, t);

	if (tick % 480 == 0)
	{
		if (++tempCounter == 4)
		{
			tempCounter = 0;
		}
		tick = 0;

		sR = wantR;
		sG = wantG;
		sB = wantB;
		sA = wantA;
		sX = wantX;
		sY = wantY;
		sS = wantS;
		sBI = wantBI;

		switch (tempCounter)
		{
			//Morning
		case 0:
			wantR = 0.1f;
			wantG = 0.1f;
			wantB = 0.1f;
			wantA = 0.5f;
			wantX = -0.5f;
			wantY = 0.5f;
			wantS = 8.0f;
			wantBI = 0.1f * bmFactor;
			break;
			//Afternoon
		case 1:
			wantR = 0.5f;
			wantG = 0.3f;
			wantB = 0.5f;
			wantA = 0.1f;
			wantX = 0.5f;
			wantY = 0.5f;
			wantS = 4.0f;
			wantBI = 0.145f * bmFactor;
			break;
			//Evening
		case 2:
			wantR = 0.8f;
			wantG = 0.3f;
			wantB = 0.5f;
			wantA = 0.2f;
			wantX = 0.5f;
			wantY = -0.5f;
			wantS = 6.0f;
			wantBI = 0.12f * bmFactor;
			break;
			//Night
		case 3:
			wantR = 0.0f;
			wantG = 0.0f;
			wantB = 0.3f;
			wantA = 0.5f;
			wantX = -0.5f;
			wantY = -0.5f;
			wantS = 12.0f;
			wantBI = 0.08f * bmFactor;
			break;
		}
	}
	tick++;
}