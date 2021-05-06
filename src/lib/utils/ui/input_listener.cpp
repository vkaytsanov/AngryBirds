//
// Created by Viktor on 13.1.2021 г..
//

#include "include/input_listener.h"
#include "../../include/lib.h"

void InputListener::handle(SDL_Event& event) {
	switch (event.type) {
		case SDL_KEYDOWN:
			keyDown(event.key.keysym.sym);
			return;
		case SDL_KEYUP:
			keyUp(event.key.keysym.sym);
			return;
		case SDL_MOUSEBUTTONDOWN:
			touchDown(event.motion.x, event.motion.y);
			return;
		case SDL_MOUSEBUTTONUP:
			touchUp(event.motion.x, event.motion.y);
			return;
	}
}

InputListener::InputListener() {
	keyDown = [&](int key) -> void {

	};
	keyUp = [&](int key) -> void {

	};
	touchDown = [&](float x, float y) -> void {
		Lib::app->log("InputListener", "touchDown");
	};
	touchUp = [&](float x, float y) -> void {
		Lib::app->log("InputListener", "touchUp");
	};
}
