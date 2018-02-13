#include "AudioManager.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "SpriteRendererManager.h"

AudioManager* AudioManager::s_instance;

AudioManager* AudioManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new AudioManager();
	return s_instance;
}

void AudioManager::release()
{
	delete s_instance;
	s_instance = NULL;
}

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
}

AudioManager::~AudioManager()
{
	Mix_Quit();
}

void AudioManager::playMusic(std::string filename, int loops, float volumeFactor)
{
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *bgm = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(1, bgm, 0);
	Mix_Volume(1, 10 * volumeFactor);
}
void AudioManager::playSEFshoot(std::string filename, int loops, float volumeFactor)
{
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *SEF = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(2, SEF, 0);
	Mix_Volume(2, 128 * volumeFactor);
}

void AudioManager::playSEFhit(std::string filename, int loops, float volumeFactor)
{
	//Mix_PlayMusic(mGameObj->GetMusic(filename), loops);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *SEF = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(3, SEF, 0);
	Mix_Volume(3, 35 * volumeFactor);
}

void AudioManager::playMusicForWin(std::string filename, int loops, float volumeFactor)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	Mix_Chunk *bgm = Mix_LoadWAV(filename.c_str());
	Mix_PlayChannel(4, bgm, 0);
	Mix_Volume(4, 50 * volumeFactor);
}

void AudioManager::pauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::resumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::stopMusic()
{
	Mix_CloseAudio();
}
