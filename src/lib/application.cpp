//
// Created by Viktor on 17.12.2020 г..
//

#include "GL/glew.h"
#include "include/application.h"
#include "include/lib.h"
#include <string>

#include <typeinfo>


Application::Application(Listener* listener) :
		Application(listener, new Configuration()) {}

Application::Application(Listener* listener, Configuration* config) :
		Application(listener, config, new Graphics(config)) {}

/* Initializing here the application */
Application::Application(Listener* listener, Configuration* config, Graphics* graphics) {

	// Our m_pGame
	this->listener = listener;
	// Our configuration file for the m_pGame
	this->config = config;
	// Our library for graphics
	this->graphics = graphics;
	// Logging, debugging and errors utility
	this->logger = new Logger();
	// Receive user input
	this->input = new Input(config->width, config->height);
	// Our library for audio
	this->audio = new Audio();
	// if we dont have declared title, we will use the name of the class
	if (config->title == nullptr) config->title = typeid(listener).name();
	// creating the m_window
	graphics->createWindow();
	// creating the environment lib
	Lib::app = this;
	Lib::graphics = graphics;
	Lib::input = input;
	Lib::audio = audio;
	// creating the objects from the m_pGame
	listener->create();
	// reset the delta time so we dont get huge value after long initialization of the game
	graphics->m_lastTime = SDL_GetTicks();
	running = true;

	gameLoop();
}

void Application::gameLoop() {
	int lastWidth = graphics->getWidth();
	int lastHeight = graphics->getHeight();
	bool wasPaused = false;

	while (running) {
		// fetching all the user input
		input->update();
		// processing the input by giving it to the processors
		input->processEvents();
		// user has clicked the front right "X" m_quit button
		if (input->shouldQuit()) break;
		bool isMinimized = !graphics->isVisible();
		bool isBackground = graphics->isBackground();
		bool isPaused = isMinimized || isBackground;
		if (!wasPaused && isPaused) {
			// the m_pGame m_window just became not active on the user's end
			wasPaused = true;
			listener->pause();
		}
		if (wasPaused && !isPaused) {
			// the m_pGame m_window just became active on the user's end
			wasPaused = false;
			listener->resume();
		}

		const int width = graphics->getWidth();
		const int height = graphics->getHeight();
		if (lastWidth != width || lastHeight != height) {
			// we should have received any changes in the input->update()
			lastWidth = width;
			lastHeight = height;
			// sending to the listener that the user has resized
			// it should update the m_pViewport if there is one
			listener->resize(width, height);
		}

		if (!isPaused) {
			graphics->updateTime();
			listener->render();
			SDL_GL_SwapWindow(graphics->getWindow());

			/* So we don't use 100% CPU */
			SDL_Delay(1);
		}
		else {
			SDL_Delay(1000);
		}
		int error;
		while ((error = glGetError()) != GL_NO_ERROR) {
			this->error("OpenGL Error", reinterpret_cast<const char*>(glewGetErrorString(error)));
		}
	}
}

void Application::exitApp() {
	running = false;
}

Application::~Application() {
	delete listener;
	delete audio;
	delete logger;
	delete graphics;
	delete config;
}

void Application::log(const char* tag, const char* message) const {
	logger->log(tag, message);
}

void Application::error(const char* tag, const char* message) const {
	logger->error(tag, message);
}

void Application::error(const char* tag, int message) const {
	logger->error(tag, std::to_string(message).c_str());
}

void Application::log(const char* tag, int message) const {
	logger->log(tag, std::to_string(message).c_str());
}

void Application::debug(const char* tag, const char* message) const {
	logger->debug(tag, message);
}



