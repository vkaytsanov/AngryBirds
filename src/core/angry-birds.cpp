//
// Created by Viktor on 23.12.2020 г..
//

#include "include/angry-birds.h"
#include "../lib/include/lib.h"
#include "systems/include/render_system.h"
#include "systems/include/debug_system.h"
#include "../lib/utils/camera/include/first_person_camera_controller.h"
#include "data/include/asset_manager.h"
#include "systems/include/transform_system.h"
#include "systems/include/physics_system.h"

#include "../lib/imgui/imgui.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/memory.hpp>

#include "components/include/sprite.h"

template <typename T>
struct SerializableComponent {
	int64_t id;
	T component;

	SerializableComponent() = default;
	SerializableComponent(int64_t id, const T& component) : id(id), component(component){}
	
	template <typename Archive>
	void serialize(Archive& archive) {
		archive(id, component);
	}
};

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
	AssetManager::getInstance();
	// glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_LEQUAL);
	// glDisable(GL_CULL_FACE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_entityX.systems.add<TransformSystem>();
	m_entityX.systems.add<PhysicsSystem>();
	m_entityX.systems.add<RenderSystem>();
	m_entityX.systems.add<DebugSystem>();
#ifdef USE_EDITOR
	m_pEditor = std::make_unique<Editor>();
#endif
	m_entityX.systems.configure();

	// {
	// entityx::Entity ent = m_entityX.entities.create();
	// 	ent.addComponent<Transform>();
	// 	ent.addComponent<RigidBody>();
	// }
	// {
	// entityx::Entity ent = m_entityX.entities.create();
	// ent.addComponent<Transform>(Vector3f(5, 3, 2));
	// }

	// auto normalPig = m_entityX.entities.create();
	// normalPig.addComponent<Transform>();
	// normalPig.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("pigs"), 679, 790, 99, 97));

	deserialize();

}

void AngryBirds::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

#ifdef USE_EDITOR
	m_pEditor->m_fbo.bind();
	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
	m_pEditor->m_fbo.unbind();

	m_pEditor->update(Lib::graphics->getDeltaTime());
#else
	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
#endif
}

void AngryBirds::renderImGui() {
#ifdef USE_EDITOR
	m_pEditor->renderImGui(m_entityX.entities);
#endif
}

void AngryBirds::pause() {

}

void AngryBirds::resume() {

}

void AngryBirds::resize(const int width, const int height) {
	//m_pGraphicsSystem->resizeViewport(width, height);
}

void AngryBirds::deserialize() {
	std::ifstream is("scene.bin");
	cereal::BinaryInputArchive archive(is);


	std::vector<SerializableComponent<Transform>> transforms;
	std::vector<SerializableComponent<RigidBody>> rigidBodys;
	std::vector<SerializableComponent<Sprite>> spriteDeserializes;

	archive(transforms);
	archive(rigidBodys);
	archive(spriteDeserializes);

	for (unsigned i = 0; i < transforms.size(); i++) {
		std::cout << "TransformX: " << transforms[i].component.position.x << "\n";
		auto entity = m_entityX.entities.create();
		entity.addComponent<Transform>(transforms[i].component);
	}

	for (unsigned i = 0; i < rigidBodys.size(); i++) {
		std::cout << "RigidBodyUseG: " << rigidBodys[i].component.m_useGravity << "\n";
		m_entityX.entities.addComponent<RigidBody>(entityx::Entity::Id(rigidBodys[i].id), rigidBodys[i].component);
	}

	for (unsigned i = 0; i < spriteDeserializes.size(); i++) {
		std::cout << "TextName: " << spriteDeserializes[i].component.m_textureRegion.getTexture()->m_name << "\n";
		m_entityX.entities.addComponent<Sprite>(entityx::Entity::Id(spriteDeserializes[i].id),
		                                        std::move(spriteDeserializes[i].component));
	}

}

void AngryBirds::serialize() {
	std::ofstream os("scene.bin");
	cereal::BinaryOutputArchive archive(os);
	std::vector<SerializableComponent<Transform>> transforms;
	std::vector<SerializableComponent<RigidBody>> rigidBodys;
	std::vector<SerializableComponent<Sprite>> spritesSerialization;

	for (auto entity : m_entityX.entities.entities_with_components<Transform>()) {
		entityx::ComponentHandle<Transform> ch = entity.getComponent<Transform>();
		SerializableComponent<Transform> td(ch.entity().id().id(), *ch);
		transforms.emplace_back(td);
	}

	for (auto entity : m_entityX.entities.entities_with_components<RigidBody>()) {
		entityx::ComponentHandle<RigidBody> ch = entity.getComponent<RigidBody>();
		SerializableComponent<RigidBody> rbd(ch.entity().id().id(), *ch);

		rigidBodys.emplace_back(rbd);
	}

	for (auto entity : m_entityX.entities.entities_with_components<Sprite>()) {
		entityx::ComponentHandle<Sprite> ch = entity.getComponent<Sprite>();
		SerializableComponent<Sprite> sc = SerializableComponent<Sprite>(ch.entity().id().id(), *ch);

		spritesSerialization.emplace_back(sc);
	}

	archive(transforms);
	archive(rigidBodys);
	archive(spritesSerialization);
}

AngryBirds::AngryBirds() {
}

AngryBirds::~AngryBirds() {
	// serialize();
}
