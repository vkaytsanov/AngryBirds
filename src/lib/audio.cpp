//
// Created by Viktor on 18.1.2021 г..
//


#include <iostream>
#include "include/audio.h"

Audio::Audio() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 1024) < 0) {
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << "\n";
	}
}

Sound Audio::newSound(const std::string& file_path) {
	return Sound(file_path);
}

Music Audio::newMusic(const std::string& file_path) {
	return Music(file_path);
}


Audio::~Audio() {
	Mix_Quit();
}

void Audio::stopMusic() {
	Mix_HaltMusic();
}
