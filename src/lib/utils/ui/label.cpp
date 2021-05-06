//
// Created by Viktor on 12.1.2021 г..
//

#include <iostream>
#include "include/label.h"
#include "../../include/lib.h"

Label::Label(const std::string& text) : Label(text, nullptr) {}

Label::Label(const LabelStyle* style) : Label("", style) {}

Label::Label(const std::string& text, const LabelStyle* style) {
	this->m_text = text;
	setStyle(style);
}

const std::string& Label::getText() const {
	return m_text;
}

void Label::setText(const std::string& text) {
	this->m_text = text;
}

void Label::draw() {
	SDL_Rect drawingRect{(int) x, (int) y, (int) width, (int) height};
	SDL_RenderCopy(Lib::graphics->getRenderer(), m_texture, nullptr, &drawingRect);
}

void Label::setStyle(const LabelStyle* style) {
	this->m_style = style;

	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(style->font, m_text.c_str(), style->color);
	m_texture = SDL_CreateTextureFromSurface(Lib::graphics->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
}

Label::~Label() {
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}

void Label::updateText() {
	SDL_DestroyTexture(m_texture);
	SDL_Surface* textSurface = TTF_RenderText_Blended(m_style->font, m_text.c_str(), m_style->color);
	m_texture = SDL_CreateTextureFromSurface(Lib::graphics->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
	// TODO Proper positioning
//		if ((align & Right) != 0) {
//			x += width;
//		}
//		else if((align & Left) != 0){
//			x += width / 2;
//		}

}

const LabelStyle* Label::getStyle() const {
	return m_style;
}

//void Label::setAlign(Align align) {
//	Label::align = align;
//}


