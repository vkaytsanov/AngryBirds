#if !defined(__EMSCRIPTEN__)
#define GLEW_STATIC
#endif


#include "../lib/include/configuration.h"
#include "../lib/include/application.h"
#include "../core/include/angry-birds.h"


int main(int argc, char* args[]) {
#if !defined(__EMSCRIPTEN__)
	auto* config = new Configuration("AngryBirds", 1920, 1080);
#else
	auto* config = new Configuration("AngryBirds", 800, 640);
#endif
	
	auto* app = new Application(new AngryBirds(), config);
	delete app;
	return 0;
}
