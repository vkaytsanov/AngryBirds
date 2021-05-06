#define GLEW_STATIC


#include "../lib/include/configuration.h"
#include "../lib/include/application.h"
#include "../core/include/angry-birds.h"




int main(int argc, char* args[]) {
	auto* config = new Configuration("AngryBirds", 1120, 700);

	auto* app = new Application(new AngryBirds(), config);

	delete app;
	return 0;
}