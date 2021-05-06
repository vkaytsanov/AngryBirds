//
// Created by Viktor on 12.1.2021 г..
//

#ifndef LABEL_STYLE_H
#define LABEL_STYLE_H


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif
#include <string>


class LabelStyle {
public:
	TTF_Font* font;
	SDL_Color color;
	SDL_Color backgroundColor = {255, 255, 255, 255};
	int size;
	LabelStyle() = default;
	explicit LabelStyle(TTF_Font* font);
	LabelStyle(TTF_Font* font, int size);
	LabelStyle(TTF_Font* font, const SDL_Color& color);
	LabelStyle(TTF_Font* font, const SDL_Color& color, int size);
};


#endif //LABEL_STYLE_H
