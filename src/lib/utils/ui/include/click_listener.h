//
// Created by Viktor on 13.1.2021 г..
//

#ifndef CLICK_LISTENER_H
#define CLICK_LISTENER_H


#include "input_listener.h"

class ClickListener : public InputListener {
public:
	ClickListener() = default;
	explicit ClickListener(std::function<void()> clicked);
	std::function<void()> clicked;
};


#endif //CLICK_LISTENER_H
