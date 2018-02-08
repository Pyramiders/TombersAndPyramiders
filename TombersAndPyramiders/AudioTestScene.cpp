#include "AudioTestScene.h"
#include "MatchManager.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include <iostream>
#include "InputManager.h"
#include "AudioManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include "Sender.h"
#include "Receiver.h"
#include "SpriteSheet.h"

void AudioTestScene::OnStart() {
	BuildBaseScene();
	GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));
	GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));
	GLuint characterTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
	GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/WalkingSpriteSheet.png"));

	// Create Players
	MatchManager::GetInstance()->CreateBattlers(Shader::GetShader(), characterTexture, spriteSheetTexture);




}

void AudioTestScene::OnEnd() {
	//delete(player1);
	//delete(player2);
}

void AudioTestScene::OnUpdate(int ticks) {
	if (InputManager::GetInstance()->onKeyPressed(SDLK_0)) {
		AudioManager::GetInstance()->PlayMusic("mario_.wav");
	}

	//player1->GetComponent<Sender*>()->SendUpdate();
	//NetworkingManagerTemp::GetInstance()->SendQueuedEvents();
}