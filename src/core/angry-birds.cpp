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
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>


struct TransformDeserialize {
	int64_t id;
	Transform transform;

	template <typename Archive>
	void serialize(Archive& archive) {
		archive(id, transform);
	}
};

struct RigidBodyDeserialize {
	int64_t id;
	RigidBody rigidBody;

	template <typename Archive>
	void serialize(Archive& archive) {
		archive(id, rigidBody);
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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);

	m_entityX.systems.add<TransformSystem>();
	m_entityX.systems.add<PhysicsSystem>();
	m_entityX.systems.add<RenderSystem>();
	m_entityX.systems.add<DebugSystem>();

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
	deserialize();

}

void AngryBirds::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
}

void AngryBirds::renderImGui() {
	ImGui::Begin("testWindow", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos({0, 0});
	ImGui::SetWindowSize({300, static_cast<float>(Lib::graphics->getHeight())});
	ImGui::End();
}

void AngryBirds::pause() {

}

void AngryBirds::resume() {

}

void AngryBirds::resize(const int width, const int height) {
	//m_pGraphicsSystem->resizeViewport(width, height);
}

void AngryBirds::deserialize() {
	std::ifstream is("scene.json");
	cereal::JSONInputArchive archive(is);


	std::vector<TransformDeserialize> transforms;
	std::vector<RigidBodyDeserialize> rigidBodys;

	archive(transforms);
	archive(rigidBodys);

	for (int i = 0; i < transforms.size(); i++) {
		std::cout << "TransformX: " << transforms[i].transform.position.x << "\n";
		auto entity = m_entityX.entities.create();
		entity.addComponent<Transform>(transforms[i].transform);
	}
	
	for (int i = 0; i < rigidBodys.size(); i++) {
		std::cout << "RigidBodyUseG: " << rigidBodys[i].rigidBody.m_useGravity << "\n";
		m_entityX.entities.assign<RigidBody>(entityx::Entity::Id(rigidBodys[i].id), rigidBodys[i].rigidBody);
	}

	std::cout << m_entityX.entities.get(entityx::Entity::Id(rigidBodys[0].id)).getComponent<Transform>()->position.x << "\n";
	
}

void AngryBirds::serialize() {
	std::ofstream os("scene.json");
	cereal::JSONOutputArchive archive(os);
	std::vector<TransformDeserialize> transforms;
	std::vector<RigidBodyDeserialize> rigidBodys;
	
	for (auto entity : m_entityX.entities.entities_with_components<Transform>()) {
		entityx::ComponentHandle<Transform> ch = entity.getComponent<Transform>();
		// transforms.emplace_back(*ch.get());
		//Transform* c = ch.get();
		TransformDeserialize td;
		td.id = ch.entity().id().id();
		td.transform = *ch;
		transforms.emplace_back(td);
	}
	
	for (auto entity : m_entityX.entities.entities_with_components<RigidBody>()) {
		entityx::ComponentHandle<RigidBody> ch = entity.getComponent<RigidBody>();
		// transforms.emplace_back(*ch.get());
		//Transform* c = ch.get();
		RigidBodyDeserialize rbd;
		rbd.id = ch.entity().id().id();
		rbd.rigidBody = *ch;
		
		rigidBodys.emplace_back(rbd);
	}
	
	archive(transforms);
	archive(rigidBodys);
}

AngryBirds::~AngryBirds() {
	serialize();
}
