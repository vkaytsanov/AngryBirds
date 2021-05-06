//
// Created by Viktor on 12.1.2021 г..
//

#include <iostream>
#include "include/user_interface.h"
#include "../../include/lib.h"
#include "include/input_listener.h"


void UserInterface::addActor(Actor* actor) {
	actor->setId(actors.size());
	actors.emplace_back(actor);
}

/** Function to apply animations or actions with the actors */
void UserInterface::act(float dt) {
	for (Actor* actor : actors) {
		if (actor->isVisible()) actor->act(dt);
	}
}

void UserInterface::draw() {

	for (Actor* actor : actors) {
		if (actor->isVisible()) actor->draw();
	}
	if (debug) {
		SDL_SetRenderDrawColor(Lib::graphics->getRenderer(), 0xff, 0xff, 0xff, 0xff);
		for (Actor* actor : actors) {
			SDL_Rect rect = {(int) actor->getX(), (int) actor->getY(), (int) actor->getWidth(),
			                 (int) actor->getHeight()};
			SDL_RenderDrawRect(Lib::graphics->getRenderer(), &rect);

		}
	}
}

UserInterface::~UserInterface() {
}


void UserInterface::keyDown(SDL_Event& e, int key) {
	for (Actor* actor : actors) {
		for (EventListener* listener : actor->getListeners()) {
			listener->handle(e);
		}
	}
}

void UserInterface::keyUp(SDL_Event& e, int key) {
	for (Actor* actor : actors) {
		for (EventListener* listener : actor->getListeners()) {
			listener->handle(e);
		}
	}
}

void UserInterface::touchDown(SDL_Event& e, float x, float y) {
	for (Actor* actor : actors) {
		if (actor->hit(x, y)) {
			for (EventListener* listener : actor->getListeners()) {
				listener->handle(e);
			}
		}
	}
}

void UserInterface::touchUp(SDL_Event& e, float x, float y) {
	Lib::app->log("InputProcessor", "touchUp");
	for (Actor* actor : actors) {
		if (actor->hit(x, y)) {
			for (EventListener* listener : actor->getListeners()) {
				listener->handle(e);
			}
		}
	}
}

/** Adds listener to the first actor in the UI */
void UserInterface::addListener(EventListener* e) {
	actors[0]->addListener(e);
}


