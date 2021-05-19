#pragma once
#include <string>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>


enum DatabaseShapeTypes {
	Box,
	Circle,
	Triangle,
	Plank,
	Ground
};

struct BodyInfo {
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;

	template <typename Archive>
	void save(Archive& archive);

	template <typename Archive>
	void load(Archive& archive);

};


class Box2dDatabase {
private:
	b2PolygonShape m_boxShape;
	b2CircleShape m_circleShape;
	b2PolygonShape m_triangleShape;
	b2PolygonShape m_plankShape;
	b2PolygonShape m_groundShape;
private:
	void createShapes();
public:
	BodyInfo m_boxBody;
	BodyInfo m_triangleBody;
	BodyInfo m_plankBody;
	BodyInfo m_groundBody;
	BodyInfo m_circleBody;
public:
	Box2dDatabase();
	b2Shape* fromTypeToShape(DatabaseShapeTypes type);

	static Box2dDatabase& getInstance();
};


template <typename Archive>
void BodyInfo::save(Archive& archive) {
	archive(bodyDef.type);
	// the shape type
	archive(fixtureDef.userData.pointer);
	archive(fixtureDef.density, fixtureDef.friction, fixtureDef.restitution);
}

template <typename Archive>
void BodyInfo::load(Archive& archive) {
	archive(bodyDef.type);
	// getting the shape enum type
	archive(fixtureDef.userData.pointer);
	// getting it from the database
	fixtureDef.shape = Box2dDatabase::getInstance().fromTypeToShape(
		static_cast<DatabaseShapeTypes>(fixtureDef.userData.pointer));
	archive(fixtureDef.density, fixtureDef.friction, fixtureDef.restitution);
}
