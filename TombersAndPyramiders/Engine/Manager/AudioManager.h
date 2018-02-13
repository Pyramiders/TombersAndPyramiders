#pragma once
#include <string>

class AudioManager
{
private:
	static AudioManager* s_instance;
	//GameObject* mGameObj;

	AudioManager();
	~AudioManager();

public:
	static AudioManager* getInstance();
	static void release();

	//Starts playing music
	void playMusic(std::string filename, int loop = -1, float volumeFactor = 1.0f);
	void playSEFhit(std::string filename, int loop = -1, float volumeFactor = 1.0f);
	void playSEFshoot(std::string filename, int loop = -1, float volumeFactor = 1.0f);
	void playMusicForWin(std::string filename, int loop = -1, float volumeFactor = 1.0f);
	//Pauses the current music
	void pauseMusic();
	//Resume playing the music
	void resumeMusic();
	//Stops playing the music
	void stopMusic();
	//Starts sound effect, plays til the end and stops
	//void PlaySoundEffect(std::string filename, int loop = 0, int channel = 0);


};
#pragma once
