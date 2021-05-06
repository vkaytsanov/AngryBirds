//
// Created by Viktor on 12.1.2021 г..
//

#include "include/event_listener.h"
#include "../../include/lib.h"


void EventListener::handle(SDL_Event& event) {
	Lib::app->log("EventListener", "Not handling");
}

EventListener::~EventListener() {
	Lib::app->log("EventListener", "Destructor");
}
