//
// Created by Viktor on 7.3.2021 г..
//

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../../lib/utils/include/shaders.h"
#include "../../../lib/utils/camera/include/perspective_camera.h"
#include "../../../lib/utils/camera/include/orthographic_camera.h"
#include "utils/camera/include/first_person_camera_controller.h"
#include "utils/include/universal_viewport.h"

#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
#include "utils/box2d/b2draw/DebugDraw.h"
#endif

class RenderSystem : public entityx::System<RenderSystem> {
private:
	UniversalViewport m_viewport;
	Shaders m_spriteShader;
	Shaders m_particleShader;
#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
	b2draw::DebugDraw* m_pDebugDraw = nullptr;
#endif
private:
	void renderSprites(entityx::EntityManager& entities);
	void renderParticles(entityx::EntityManager& entities);
public:
	OrthographicCamera m_camera;
	RenderSystem();
#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
	RenderSystem(b2draw::DebugDraw* debugDraw);
#endif
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void onResize(const int width, const int height);
};


#endif //RENDER_SYSTEM_H
