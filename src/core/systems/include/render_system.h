//
// Created by Viktor on 7.3.2021 г..
//

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../../lib/utils/include/shaders.h"
#include "../../../lib/utils/camera/include/perspective_camera.h"
#include "../../../lib/utils/camera/include/orthographic_camera.h"


class RenderSystem : public entityx::System<RenderSystem>{
private:
	static constexpr int RENDER_DISTANCE = 3;

	PerspectiveCamera m_camera;
	Transform* m_pPlayerTransform;

public:
	RenderSystem();
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};


#endif //RENDER_SYSTEM_H
