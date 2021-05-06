//
// Created by Viktor on 13.1.2021 г..
//

#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H



struct InputProcessor {
	virtual void touchDown(SDL_Event& e, float x, float y);
	virtual void touchUp(SDL_Event& e, float x, float y);
	virtual void keyDown(SDL_Event& e, int key);
	virtual void keyUp(SDL_Event& e, int key);
};


#endif //INPUT_PROCESSOR_H
