//
// Created by Viktor on 12.1.2021 г..
//

#include "include/label_style.h"
#include "../../include/lib.h"

LabelStyle::LabelStyle(TTF_Font* font, const SDL_Color& color, int size) : font(font), color(color), size(size) {
}

LabelStyle::LabelStyle(TTF_Font* font, int size) : LabelStyle(font, {255, 255, 255, 255}, size) {}

LabelStyle::LabelStyle(TTF_Font* font) : LabelStyle(font, 16) {}

LabelStyle::LabelStyle(TTF_Font* font, const SDL_Color& color) {
	this->font = font;
	this->color = color;
}
