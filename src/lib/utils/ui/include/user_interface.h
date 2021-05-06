//
// Created by Viktor on 12.1.2021 г..
//

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include <vector>
#include "actor.h"
#include "../../include/input_processor.h"

class UserInterface : public InputProcessor {
private:
	// TODO Use KD/BVH Tree
	std::vector<Actor*> actors;
public:
	~UserInterface();
	bool debug = false;
	void addActor(Actor* actor);
	void act(float dt);
	void draw();
	void keyDown(SDL_Event& e, int key) override;
	void touchDown(SDL_Event& e, float x, float y) override;
	void touchUp(SDL_Event& e, float x, float y) override;
	void keyUp(SDL_Event& e, int key) override;
	void addListener(EventListener* e);
};


#endif //USER_INTERFACE_H
