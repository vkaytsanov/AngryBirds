#if defined(__EMSCRIPTEN__)
#include "include/gles_graphics.h"
#else
#define GLEW_STATIC
#include "include/gl_graphics.h"
#endif


#include "../lib/include/configuration.h"
#include "../lib/include/application.h"
#include "../core/include/angry-birds.h"


int main(int argc, char* args[]) {
	// auto* config = new Configuration("AngryBirds", 1080, 560);
	auto* config = new Configuration("AngryBirds", 1920, 1080);
#if !defined(__EMSCRIPTEN__)
	auto* app = new Application(new AngryBirds(), config, new GLGraphics(config));
#else
	config->width = 800;
	config->height = 640;
	auto* app = new Application(new AngryBirds(), config, new GLESGraphics(config));
#endif
	delete app;
	return 0;
}
