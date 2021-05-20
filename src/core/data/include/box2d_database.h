#pragma once
#include <string>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>

#include "prefab_database.h"


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
	
	// Serialization
	PrefabType prefabType;
	
	template <typename Archive>
	void serialize(Archive& archive) {
		archive(prefabType);
	}
	
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
	BodyInfo& fromTypeToBody(PrefabType type);

	static Box2dDatabase& getInstance();
};