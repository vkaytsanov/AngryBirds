//
// Created by Viktor on 18.1.2021 г..
//

#ifndef MUSIC_H
#define MUSIC_H


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <string>

class Music {
private:
	Mix_Music* rawMusic;
public:
	Music() = default;
	Music(const std::string& file_path);
	~Music();
	void loadMusic(const std::string& file_path);
	void play(bool loopable);
	void free();
};


#endif //MUSIC_H
