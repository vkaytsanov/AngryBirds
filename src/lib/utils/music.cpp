//
// Created by Viktor on 18.1.2021 г..
//

#include "include/music.h"

Music::Music(const std::string& file_path) {
	rawMusic = Mix_LoadMUS(file_path.c_str());
	if (rawMusic == nullptr) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		exit(-1);
	}
}

void Music::loadMusic(const std::string& file_path) {
	rawMusic = Mix_LoadMUS(file_path.c_str());
	if (rawMusic == nullptr) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		exit(-1);
	}
}

void Music::play(bool loopable) {
	Mix_PlayMusic(rawMusic, loopable ? -1 : 0);
}

void Music::free() {
	if (rawMusic) {
		Mix_FreeMusic(rawMusic);
		rawMusic = nullptr;
	}
}

Music::~Music() {
	free();
}
