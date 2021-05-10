//
// Created by Viktor on 7.3.2021 г..
//

#include "include/render_system.h"
#include "../components/include/sprite.h"

RenderSystem::RenderSystem() : m_camera(),
                               m_spriteShader("textures/shader.vert", "textures/shader.frag"),
                               fpsController(&m_camera) {

}

void RenderSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	m_camera.m_pTransform = new Transform();
}

void RenderSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	//fpsController.update(dt);
}

void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void RenderSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	
	m_camera.update(true);
	
	m_spriteShader.begin();


	m_spriteShader.setMatrix4("combinedMatrix", m_camera.getCombinedMatrix());
	
	glActiveTexture(GL_TEXTURE0);
	for (auto entity : entities.entities_with_components<Sprite>()) {
		Sprite* ch = entity.getComponent<Sprite>().get();

		m_spriteShader.setMatrix4("modelMatrix", entity.getComponent<Transform>()->transformMatrix);
		glBindTexture(GL_TEXTURE_2D, ch->m_textureRegion.getTexture()->getBuffer());

		ch->getVao()->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		ch->getVao()->unbind();
	}

	m_spriteShader.end();

}
