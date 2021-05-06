//
// Created by Viktor on 18.1.2021 г..
//

#ifndef SOUND_H
#define SOUND_H


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif
#include <string>

class Sound {
private:
	Mix_Chunk* rawSound;
public:
	Sound(const std::string& file_path);
	~Sound();
	void loadSound(const std::string& file_path);
	void play(int channel = -1, bool loopable = false);
	void stop(int channel = -1);

};


#endif //SOUND_H
