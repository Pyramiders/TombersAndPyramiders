#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
/*
int main(int argc, char *argv) {
	SDL_AudioInit;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "ERROR: " << Mix_GetError() << std::endl;


	Mix_Music *bgm = Mix_LoadMUS("mario_.mp3");
	Mix_Chunk *soundEffect = Mix_LoadWAV("");

	bool isRunning = true;
	SDL_Event ev;
	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym) {
				case SDLK_p:
					if (!Mix_PlayingMusic())
						Mix_PlayMusic(bgm, -1);
					else if (Mix_PausedMusic())
						Mix_ResumeMusic();
					else
						Mix_PauseMusic();
					break;
				case SDLK_s:
					Mix_HaltMusic();
					break;
				}
				
			}
		}
	}


	Mix_FreeChunk(soundEffect);
	Mix_FreeMusic(bgm);

	bgm = nullptr;
	soundEffect = nullptr;
	Mix_Quit();
	return 0;


}
*/