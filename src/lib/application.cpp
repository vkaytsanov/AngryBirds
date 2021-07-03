//
// Created by Viktor on 17.12.2020 г..
//


#include "include/application.h"
#include "include/lib.h"
#include <string>

#include <typeinfo>



#if defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <SDL2/SDL.h>
#else
#include "GL/glew.h"
#include <SDL2/SDL.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#endif


#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// TODO Refactor this in other application class
#if defined(__EMSCRIPTEN__)
void emscriptenLoop(void* arg) {
	Application* app = static_cast<Application*>(arg);
	app->log("Application", "updating");
	// fetching all the user input
	app->input->update();
	// processing the input by giving it to the processors
	app->input->processEvents();

	app->graphics->updateTime();
	app->listener->render();

	emscripten_sleep(10);

}
#endif

/* Initializing here the application */
Application::Application(Listener* listener, Configuration* config, IGraphics* graphics) {

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
	// initializing the current graphics api
	graphics->initialize();
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
#if defined(__EMSCRIPTEN__)
	emscripten_set_main_loop_arg(&emscriptenLoop, this, -1, 1);
#else
	gameLoop();
#endif
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
		const bool isMinimized = !graphics->isVisible();
		const bool isBackground = graphics->isBackground();
		const bool isPaused = isMinimized || isBackground;
		if (!wasPaused && isPaused) {
			// the m_pGame m_pWindow just became not active on the user's end
			wasPaused = true;
			listener->pause();
		}
		if (wasPaused && !isPaused) {
			// the m_pGame m_pWindow just became active on the user's end
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
			graphics->swapBuffers(listener);
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

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
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
