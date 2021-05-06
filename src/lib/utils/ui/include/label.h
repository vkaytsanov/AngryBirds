//
// Created by Viktor on 12.1.2021 г..
//

#ifndef LABEL_H
#define LABEL_H


#include <string>
#include "actor.h"
#include "label_style.h"

//enum Align {
//	Center = 0b0000,
//	Top = 0b0001,
//	Bottom = 0b0010,
//	Left = 0b0100,
//	Right = 0b1000,
//};

class Label : public Actor {
private:
	std::string m_text;
	const LabelStyle* m_style;
	SDL_Texture* m_texture;
	//Align align = Left;
public:
	Label() = default;
	Label(const std::string& text, const LabelStyle* style);
	Label(const LabelStyle* style);
	Label(const std::string& text);
	~Label();
	const std::string& getText() const;
	void setText(const std::string& text);
	void setStyle(const LabelStyle* style);
	void updateText();
	void draw() override;
	const LabelStyle* getStyle() const;
	//void setAlign(Align align);
};


#endif //LABEL_H
