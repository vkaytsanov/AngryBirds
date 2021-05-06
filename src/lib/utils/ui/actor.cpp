//
// Created by Viktor on 12.1.2021 г..
//

#include "include/actor.h"

const std::vector<EventListener*>& Actor::getListeners() {
	return listeners;
}

void Actor::setListeners(const std::vector<EventListener*>& listeners) {
	Actor::listeners = listeners;
}

float Actor::getX() const {
	return x;
}

void Actor::setX(const float x) {
	Actor::x = x;
}

float Actor::getY() const {
	return y;
}

void Actor::setY(const float y) {
	Actor::y = y;
}

void Actor::setPosition(const float x, const float y) {
	this->x = x;
	this->y = y;
}

void Actor::setSize(const float width, const float height) {
	this->width = width;
	this->height = height;
}

void Actor::addListener(EventListener* e) {
	listeners.emplace_back(e);
}

void Actor::act(const float dt) {

}

Actor::Actor(const int ID) : ID(ID) {}

int Actor::getId() const {
	return ID;
}

void Actor::setId(const int id) {
	ID = id;
}

float Actor::getWidth() const {
	return width;
}

float Actor::getHeight() const {
	return height;
}


void Actor::setWidth(const float width) {
	Actor::width = width;
}

void Actor::setHeight(const float height) {
	Actor::height = height;
}

bool Actor::isVisible() const {
	return visible;
}

void Actor::setVisible(const bool visible) {
	Actor::visible = visible;
}

bool Actor::hit(const float mouseX, const float mouseY) {
	return x < mouseX && mouseX < (x + width) &&
	       y < mouseY && mouseY < (y + height);
}

Actor::~Actor() {
	for (EventListener* listener : listeners) {
		delete listener;
	}
}
