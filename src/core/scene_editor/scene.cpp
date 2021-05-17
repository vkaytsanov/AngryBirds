#include "include/scene.h"

#include <fstream>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "../components/include/serializable.h"
#include "../components/2d/include/sprite.h"
#include "../components/3d/include/rigid_body.h"


Scene::Scene(std::string name) : m_fileName(std::move(name)) {
}

void Scene::load(entityx::EntityManager* entities) {
	std::ifstream is(SCENES_PATH + m_fileName + ".bin");
	cereal::BinaryInputArchive archive(is);


	std::vector<SerializableComponent<Transform>> transforms;
	std::vector<SerializableComponent<RigidBody>> rigidBodys;
	std::vector<SerializableComponent<Sprite>> spriteDeserializes;

#ifdef _DEBUG
	// we can have empty file when we are developing the scenes
	try {
		archive(transforms);
		archive(rigidBodys);
		archive(spriteDeserializes);
	}
	catch (std::exception&) {
		return;
	}
#else
	archive(transforms);
	archive(rigidBodys);
	archive(spriteDeserializes);
#endif


	for (unsigned i = 0; i < transforms.size(); i++) {
		std::cout << "TransformX: " << transforms[i].component.position.x << "\n";
		auto entity = entities->create();
		entity.addComponent<Transform>(transforms[i].component);
	}

	for (unsigned i = 0; i < rigidBodys.size(); i++) {
		std::cout << "RigidBodyUseG: " << rigidBodys[i].component.m_useGravity << "\n";
		entities->addComponent<RigidBody>(entityx::Entity::Id(rigidBodys[i].id), rigidBodys[i].component);
	}

	for (unsigned i = 0; i < spriteDeserializes.size(); i++) {
		std::cout << "TextName: " << spriteDeserializes[i].component.m_textureRegion.getTexture()->m_name << "\n";
		entities->addComponent<Sprite>(entityx::Entity::Id(spriteDeserializes[i].id), std::move(spriteDeserializes[i].component));
	}
}

void Scene::save(entityx::EntityManager* entities) {
	std::ofstream os(SCENES_PATH + m_fileName + ".bin");
	cereal::BinaryOutputArchive archive(os);

	std::vector<SerializableComponent<Transform>> transforms;
	std::vector<SerializableComponent<RigidBody>> rigidBodys;
	std::vector<SerializableComponent<Sprite>> spritesSerialization;

	for (auto entity : entities->entities_with_components<Transform>()) {
		entityx::ComponentHandle<Transform> ch = entity.getComponent<Transform>();
		SerializableComponent<Transform> td(ch.entity().id().id(), *ch);
		transforms.emplace_back(td);
	}

	for (auto entity : entities->entities_with_components<RigidBody>()) {
		entityx::ComponentHandle<RigidBody> ch = entity.getComponent<RigidBody>();
		SerializableComponent<RigidBody> rbd(ch.entity().id().id(), *ch);

		rigidBodys.emplace_back(rbd);
	}

	for (auto entity : entities->entities_with_components<Sprite>()) {
		entityx::ComponentHandle<Sprite> ch = entity.getComponent<Sprite>();
		SerializableComponent<Sprite> sc = SerializableComponent<Sprite>(ch.entity().id().id(), *ch);

		spritesSerialization.emplace_back(sc);
	}

	archive(transforms);
	archive(rigidBodys);
	archive(spritesSerialization);
}
