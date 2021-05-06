//
// Created by Viktor on 23.12.2020 г..
//

#include "include/angry-birds.h"
#include "../lib/include/lib.h"
#include "systems/include/render_system.h"
#include "systems/include/debug_system.h"
#include "../lib/utils/camera/include/first_person_camera_controller.h"
#include "systems/include/transform_system.h"
#include "systems/include/physics_system.h"


void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s m_type = 0x%x, severity = 0x%x, message = %s\n",
	        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	        type, severity, message);
}

void AngryBirds::create() {
	//
	// glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	// glEnable(GL_DEBUG_OUTPUT);
	// glDebugMessageCallback(MessageCallback, 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);

	m_entityX.systems.add<TransformSystem>();
	m_entityX.systems.add<PhysicsSystem>();
	m_entityX.systems.add<RenderSystem>();
	m_entityX.systems.add<DebugSystem>();

	m_entityX.systems.configure();

}

void AngryBirds::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4, 0.4, 0.4, 1.0);

	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
}

void AngryBirds::pause() {

}

void AngryBirds::resume() {

}

void AngryBirds::resize(const int width, const int height) {
	//m_pGraphicsSystem->resizeViewport(width, height);
}

AngryBirds::~AngryBirds() {
}

