#include "include/scene.h"

#include <fstream>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "../components/include/serializable.h"
#include "../components/include/bird.h"
#include "../components/include/pig.h"
#include "../components/include/obstacle.h"
#include "../components/include/transform.h"
#include "../data/include/entity_factory.h"


Scene::Scene(std::string name) : m_fileName(std::move(name)) {
}

void Scene::load(entityx::EntityManager* entities) {
	std::ifstream is(SCENES_PATH + m_fileName + ".bin");
	cereal::BinaryInputArchive archive(is);


	std::vector<SerializableComponent<Transform>> transforms;
	transforms.reserve(64);

#ifdef _DEBUG
	// we can have empty file when we are developing the scenes
	try {
		archive(transforms);
	}
	catch (std::exception&) {
		return;
	}
#else
	archive(transforms);
#endif


	for (unsigned i = 0; i < transforms.size(); i++) {
		auto entity = EntityFactory::createEntityFromType(*entities, transforms[i].type);
		entity.replace<Transform>(transforms[i].component);
	}
	Lib::app->log("SceneManager", ("Scene " + m_fileName + " loaded with " + std::to_string(transforms.size()) + " entities.").c_str());
	glGetError();
}

/**
 * we need to serialize only object types with transform components
 * the rest we are gonna initialize run-time from #EntityFactory::createEntityFromType
 */

void Scene::save(entityx::EntityManager* entities) {
	std::ofstream os(SCENES_PATH + m_fileName + ".bin");
	cereal::BinaryOutputArchive archive(os);

	std::vector<SerializableComponent<Transform>> transforms;
	transforms.reserve(entities->size());

	for (auto entity : entities->entities_with_components<Bird>()) {
		auto transform = entity.getComponent<Transform>();
		auto birdType = entity.getComponent<Bird>()->type;
		SerializableComponent<Transform> td(birdType, *transform);
		transforms.emplace_back(td);
	}

	for (auto entity : entities->entities_with_components<Pig>()) {
		auto transform = entity.getComponent<Transform>();
		auto pigType = entity.getComponent<Pig>()->type;
		SerializableComponent<Transform> td(pigType, *transform);
		transforms.emplace_back(td);
	}

	for (auto entity : entities->entities_with_components<Obstacle>()) {
		auto transform = entity.getComponent<Transform>();
		auto obstacleType = entity.getComponent<Obstacle>()->type;
		SerializableComponent<Transform> td(obstacleType, *transform);
		transforms.emplace_back(td);
	}

	archive(transforms);
}
