#ifndef APPLICATION
#define APPLICATION

#include "listener.h"
#include "logger.h"
#include "graphics.h"
#include "input.h"
#include "audio.h"


class Application {
#if !defined(__EMSCRIPTEN__)
private:
#else
public:
#endif
	bool running;
	Listener* listener;
	Input* input;
	Configuration* config;
	IGraphics* graphics;
	Logger* logger;
	Audio* audio;
private:
	void exitApp();
public:
	void gameLoop();
	Application(Listener* listener, Configuration* config, IGraphics* graphics);
	~Application();
	void log(const char* tag, const char* message) const;
	void log(const char* tag, int message) const;
	void error(const char* tag, const char* message) const;
	void error(const char* tag, int message) const;
	void debug(const char* tag, const char* message) const;
};


#endif