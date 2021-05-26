﻿#pragma once

#include <array>

#if !defined(__EMSCRIPTEN__)
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#else
#include "box2d-emscripten/Dynamics/b2Fixture.h"
#include "box2d-emscripten/Collision/Shapes/b2CircleShape.h"
#include "box2d-emscripten/Collision/Shapes/b2PolygonShape.h"
#include "box2d-emscripten/Dynamics/b2Body.h"
#endif

#include "entity_type.h"



struct BodyInfo {
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	
	// Serialization
	EntityType entityType = Undefined;
	
	template <typename Archive>
	void serialize(Archive& archive) {
		archive(entityType);
	}
	
};


class Box2dDatabase {
private:
	std::array<BodyInfo, ENTITY_TYPE_SIZE> m_bodies;
	b2PolygonShape m_boxShape;
	b2CircleShape m_circleShape;
	b2PolygonShape m_triangleShape;
	b2PolygonShape m_plankShape;
	b2PolygonShape m_groundShape;
	b2PolygonShape m_chuckShape;
	b2CircleShape m_redShape;
private:
	void createShapes();
public:
	BodyInfo m_groundBody;
public:
	Box2dDatabase();
	BodyInfo& fromTypeToBody(EntityType type);

	static Box2dDatabase& getInstance();
};