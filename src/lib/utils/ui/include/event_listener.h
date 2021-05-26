//
// Created by Viktor on 12.1.2021 г..
//

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <functional>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class EventListener {
public:
	virtual void handle(SDL_Event& event);
	~EventListener();
};


#endif //EVENT_LISTENER_H
