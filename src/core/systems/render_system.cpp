//
// Created by Viktor on 7.3.2021 г..
//

#include "include/render_system.h"


RenderSystem::RenderSystem() :m_camera(70) {

}

void RenderSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	m_camera.m_pTransform = new Transform();
}

void RenderSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
}

void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void RenderSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	m_camera.update(true);
}
