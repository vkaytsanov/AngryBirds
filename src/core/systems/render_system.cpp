//
// Created by Viktor on 7.3.2021 г..
//

#include "include/render_system.h"
#include "../components/2d/include/sprite.h"
#include "../components/include/particle_emitter.h"
#include "../components/include/obstacle.h"

RenderSystem::RenderSystem() : m_viewport(240, 120, &m_camera),
                               m_spriteShader("textures/shader.vert", "textures/shader.frag"),
                               m_particleShader("particle/shader.vert", "particle/shader.frag") {

	m_camera.m_pTransform = new Transform();
	onResize(Lib::graphics->getWidth(), Lib::graphics->getHeight());
}

RenderSystem::RenderSystem(b2draw::DebugDraw* debugDraw) :
	m_viewport(240, 120, &m_camera),
	m_spriteShader("textures/shader.vert", "textures/shader.frag"),
	m_particleShader("particle/shader.vert", "particle/shader.frag"),
	m_pDebugDraw(debugDraw) {

	m_camera.m_pTransform = new Transform();
	onResize(Lib::graphics->getWidth(), Lib::graphics->getHeight());
}

void RenderSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {

}

void RenderSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	//fpsController.update(dt);
}

void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
}

void RenderSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	m_camera.update(true);

	renderSprites(entities);
	renderParticles(entities);

#if defined(_DEBUG)
	if (m_pDebugDraw) {
		m_pDebugDraw->Render(&m_camera.getCombinedMatrix());
	}
#endif
}

void RenderSystem::renderSprites(entityx::EntityManager& entities) {
	m_spriteShader.begin();
	m_spriteShader.setMatrix4("combinedMatrix", m_camera.getCombinedMatrix());
	glActiveTexture(GL_TEXTURE0);

	for (auto entity : entities.entities_with_components<Sprite>()) {
		Sprite* ch = entity.getComponent<Sprite>().get();
		glBindTexture(GL_TEXTURE_2D, ch->m_textureRegion.getTexture()->getBuffer());
		m_spriteShader.setMatrix4("modelMatrix", entity.getComponent<Transform>()->transformMatrix);

		ch->getVao()->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	VertexArray::unbind();
	m_spriteShader.end();
}

void RenderSystem::renderParticles(entityx::EntityManager& entities) {
	m_particleShader.begin();

	m_particleShader.setMatrix4("projView", m_camera.getCombinedMatrix());
	m_particleShader.setInt("tex_id", 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, AssetManager::getInstance().getSprite("all-in-one")->getBuffer());

	for (entityx::Entity entity : entities.entities_with_components<ParticleEmitter>()) {
		auto emitter = entity.getComponent<ParticleEmitter>();
		emitter->vao.bind();
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, emitter->particles.size());
	}
	VertexArray::unbind();
	m_particleShader.end();
}

void RenderSystem::onResize(const int width, const int height) {
	m_viewport.update(width, height, false);
}
