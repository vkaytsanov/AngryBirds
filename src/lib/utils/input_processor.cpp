//
// Created by Viktor on 13.1.2021 г..
//

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "include/input_processor.h"


void InputProcessor::keyDown(SDL_Event& e, int key) {

}

void InputProcessor::keyUp(SDL_Event& e, int key) {

}

void InputProcessor::touchDown(SDL_Event& e, float x, float y) {

}

void InputProcessor::touchUp(SDL_Event& e, float x, float y) {

}
