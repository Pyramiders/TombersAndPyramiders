/*
	Audio Manager

	*Last update - March 18, 2018
		- Changed to a channel oriented system
		- Added distance sound effects functionality

	@author Kevin Han
*/

#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "Audio\AudioBank.h"
#include "HelperFunctions.h"
#include "GameObject.h"
#include "SpriteRendererManager.h"
#include "Transform.h"

#define MAX_CHANNELS 16
#define MIN_DISTANCE 25
#define MAX_DISTANCE 40
#define MAX_VOLUME 128
#define DISTANCE_OFFSET 4
#define DISTANCE_VOLUME 100

#define PATH_MUSIC_MENU "Game/Assets/Audio/SpectralSands.mp3"
#define PATH_MUSIC_LEVEL_1 "Game/Assets/Audio/MystifyingTombs.mp3"

#define PATH_SFX_HIT "Game/Assets/Audio/Hit.mp3"
#define PATH_SFX_SWORD "Game/Assets/Audio/Sword.mp3"
#define PATH_SFX_BOW "Game/Assets/Audio/Arrow.mp3"
#define PATH_SFX_SHIELD "Game/Assets/Audio/Shield.mp3"
#define PATH_SFX_DASH "Game/Assets/Audio/Dash.mp3"
#define PATH_SFX_DOOR "Game/Assets/Audio/Door.mp3"
#define PATH_SFX_BUTTON_HOVER "Game/Assets/Audio/Torch.mp3"

class AudioManager
{
private:
	static AudioManager* s_instance;

	GameObject* m_listener;
	std::map<int, Mix_Chunk*> m_audioFiles;

	Mix_Chunk* m_hit;
	Mix_Chunk* m_shootArrow;
	Mix_Chunk* m_swordSwing;
	Mix_Chunk* m_valiantWind;
	Mix_Chunk* m_ignite;

	float m_distance;
	float m_listenerX;
	float m_listenerY;

	AudioManager();
	~AudioManager();

public:
	static AudioManager* getInstance();
	static void release();
	void setListener(GameObject* listenerObject);
	void playMusic(int musicInput);
	void pauseMusic();
	void resumeMusic();
	void playSound(int sfxInput, float x, float y);
	void playChannel(int channel, int volume, int distance, int sfxInput);
	void closeAudio();
};
