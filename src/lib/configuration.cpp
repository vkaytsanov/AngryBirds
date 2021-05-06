#include "include/configuration.h"

Configuration::Configuration() : Configuration("") {}

Configuration::Configuration(const char* title) : Configuration(title, 640, 480) {}

Configuration::Configuration(const int width, const int height) : Configuration("", width, height) {}

Configuration::Configuration(const char* title, const int width, const int height) {
	this->title = title;
	this->width = width;
	this->height = height;
}


