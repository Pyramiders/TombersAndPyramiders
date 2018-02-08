#include "AISelectionMenuScene.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "GLHeaders.h"
#include "Scenes.h"
#include "SceneManager.h"
#include "Transform.h"
#include "GameManager.h"

AISelectionMenuScene::AISelectionMenuScene() {}

void AISelectionMenuScene::OnStart() {
	BuildBaseScene();
	//title = new SimpleSprite("1235.png", 0.0f, 0.0f, 0.0f, GAME_WIDTH);
	title = new SimpleSprite("frameLeft.s.png", getGameLeftX() + getGameWidth() / 4.0f, getGameTopY() - getGameHeight() / 6.0f, 0.0f, GAME_WIDTH * 0.4f);
	ai2Preview = new SimpleSprite("frameRight.s.png", getGameRightX() - getGameWidth() / 4.0f, getGameTopY() - getGameHeight() / 6.0f, 0.0f, GAME_WIDTH * 0.4f);
	oneStatus = new SimpleSprite("left.s.png", getGameLeftX() + getGameWidth() / 4.0f, getGameBottomY() + getGameHeight() / 2.5f, 0.0f, GAME_WIDTH * 0.4f);
	twoStatus = new SimpleSprite("right.s.png", getGameRightX() - getGameWidth() / 4.0f, getGameBottomY() + getGameHeight() / 2.5f, 0.0f, GAME_WIDTH * 0.4f);
	p1Done = false;
	p2Done = false;
}

void AISelectionMenuScene::OnPause() {
	DestroyBaseScene();
	GameManager::GetInstance()->RemoveGameObject(title);
	GameManager::GetInstance()->RemoveGameObject(ai1Preview);
	GameManager::GetInstance()->RemoveGameObject(ai2Preview);
	GameManager::GetInstance()->RemoveGameObject(ai3Preview);
	GameManager::GetInstance()->RemoveGameObject(oneStatus);
	GameManager::GetInstance()->RemoveGameObject(twoStatus);
}

AISelectionMenuScene::~AISelectionMenuScene() {
	//delete(winnerText);
	//delete(spaceToReturnText);
}


void AISelectionMenuScene::OnUpdate(int ticks) {
	InputManager* inputManager = InputManager::GetInstance();
	if (inputManager->onKeyPressed(SDLK_a) && !p1Done) {
		p1Result = 1;
		p1Done = true;
		TryEnd();
	}
	if (inputManager->onKeyPressed(SDLK_s) && !p1Done) {
		p1Result = 2;
		p1Done = true;
		TryEnd();
	}
	if (inputManager->onKeyPressed(SDLK_d) && !p1Done) {
		p1Result = 3;
		p1Done = true;
		TryEnd();
	}

	if (inputManager->onKeyPressed(SDLK_j) && !p2Done) {
		p2Result = 1;
		p2Done = true;
		TryEnd();
	}
	if (inputManager->onKeyPressed(SDLK_k) && !p2Done) {
		p2Result = 2;
		p2Done = true;
		TryEnd();
	}

	if (inputManager->onKeyPressed(SDLK_l) && !p2Done) {
		p2Result = 3;
		p2Done = true;
		TryEnd();
	}
}


bool AISelectionMenuScene::TryEnd() {
	if (p1Done && p2Done) {
		SceneManager::GetInstance()->PushScene(new SceneTemplate(p1Result, p2Result));
	}

	return false;
}