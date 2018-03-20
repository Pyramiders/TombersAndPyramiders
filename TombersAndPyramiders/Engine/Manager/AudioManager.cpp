/*
	Audio Manager

	*Last update - March 18, 2018
		- Changed to a channel oriented system
		- Added distance sound effects functionality

	@author Kevin Han
*/

#include "AudioManager.h"

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

	Mix_AllocateChannels(MAX_CHANNELS);
	m_audioFiles[MUSIC_MENU] = Mix_LoadWAV(BuildPath(PATH_MUSIC_MENU).c_str());
	m_audioFiles[MUSIC_LEVEL_1] = Mix_LoadWAV(BuildPath(PATH_MUSIC_LEVEL_1).c_str());
	m_audioFiles[SFX_BOW] = Mix_LoadWAV(BuildPath(PATH_SFX_BOW).c_str());
	m_audioFiles[SFX_HIT] = Mix_LoadWAV(BuildPath(PATH_SFX_HIT).c_str());
	m_audioFiles[SFX_SWORD] = Mix_LoadWAV(BuildPath(PATH_SFX_SWORD).c_str());
	m_audioFiles[SFX_SHIELD] = Mix_LoadWAV(BuildPath(PATH_SFX_SHIELD).c_str());
	m_audioFiles[SFX_DASH] = Mix_LoadWAV(BuildPath(PATH_SFX_DASH).c_str());
	m_audioFiles[SFX_DOOR] = Mix_LoadWAV(BuildPath(PATH_SFX_DASH).c_str());
	m_audioFiles[SFX_BUTTON_HOVER] = Mix_LoadWAV(BuildPath(PATH_SFX_BUTTON_HOVER).c_str());
}

AudioManager::~AudioManager()
{
	Mix_Quit();
}

void AudioManager::setListener(GameObject* listenerObject)
{
	m_listener = listenerObject;
}

//Music will be looped on Channel 0
void AudioManager::playMusic(int musicInput)
{
	if (!Mix_Volume(0, MAX_VOLUME))
	{
		printf("Mix_Volume: %s\n", Mix_GetError());
	}
	if (!Mix_PlayChannel(0, m_audioFiles[musicInput], -1))
	{
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
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

//Sound effects has a pool of 15 channels to play on
void AudioManager::playSound(int sfxInput, float sourceX, float sourceY)
{
	//loop through channels to find first available
	for (int i = 1; i < MAX_CHANNELS; ++i)
	{
		if (!Mix_Playing(i))
		{
			//checks for listener
			if (m_listener != nullptr)
			{
				m_listenerX = m_listener->getTransform()->getX();
				m_listenerY = m_listener->getTransform()->getY();
				//checks distance between player and source
				m_distance = sqrt(pow((sourceX - m_listenerX), 2.0) + pow((sourceY - m_listenerY), 2.0));
			}
			else
			{
				//std::cout << "No listener found!" << endl;
				m_distance = 0;
				//break;
			}

			//play normally when source is withing range of the player
			if (m_distance < MIN_DISTANCE)
			{
				playChannel(i, MAX_VOLUME, m_distance, sfxInput);
				break;
			}
			//set the distance and volume of the channel when the source is further away
			else if (m_distance < MAX_DISTANCE)
			{
				m_distance *= DISTANCE_OFFSET;
				playChannel(i, DISTANCE_VOLUME, m_distance, sfxInput);
				break;
			}
		}
	}
}

void AudioManager::playChannel(int channel, int volume, int distance, int sfxInput)
{
	if (!Mix_Volume(channel, volume))
	{
		printf("Mix_Volume: %s\n", Mix_GetError());
	}
	if (!Mix_SetDistance(channel, distance))
	{
		printf("Mix_Volume: %s\n", Mix_GetError());
	}
	if (!Mix_PlayChannel(channel, m_audioFiles[sfxInput], 0))
	{
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
}

void AudioManager::closeAudio()
{
	Mix_CloseAudio();
}
