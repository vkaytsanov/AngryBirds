//
// Created by Viktor on 13.1.2021 г..
//

#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H


#include "event_listener.h"

class InputListener : public EventListener {
public:
	InputListener();
	void handle(SDL_Event& event) override;
	std::function<void(int)> keyDown;
	std::function<void(int)> keyUp;
	std::function<void(float x, float y)> touchDown;
	std::function<void(float x, float y)> touchUp;
//    void keyDown(int key);
//    void keyUp(int key);
//    virtual void touchDown(float x, float y);
//    virtual void touchUp(float x, float y);
};


#endif //INPUT_LISTENER_H
