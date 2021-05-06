//
// Created by Viktor on 13.1.2021 г..
//

#include "include/click_listener.h"

#include <utility>
#include "../../include/lib.h"


ClickListener::ClickListener(std::function<void()> clicked) {
	this->clicked = std::move(clicked);
	this->touchUp = [&](float x, float y) {
		this->clicked();
		Lib::app->log("ClickListener", "touchUp");
	};
}
