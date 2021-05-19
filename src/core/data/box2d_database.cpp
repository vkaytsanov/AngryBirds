#include "include/box2d_database.h"

void Box2dDatabase::createShapes() {
	m_boxShape.SetAsBox(5, 5);

	b2Vec2 vertices[3] = {
		{-5, -5},
		{5, -5},
		{0, 5}
	};
	m_triangleShape.Set(vertices, 3);

	m_plankShape.SetAsBox(10, 2);

	m_circleShape.m_radius = 5.f;

	m_groundShape.SetAsBox(200, 20);

	
}

Box2dDatabase::Box2dDatabase() {
	createShapes();
	// Box
	m_boxBody.bodyDef.type = b2_dynamicBody;

	// Serialization
	m_boxBody.fixtureDef.userData.pointer = Box;
	
	m_boxBody.fixtureDef.shape = &m_boxShape;
	m_boxBody.fixtureDef.density = 0.2f;
	m_boxBody.fixtureDef.friction = 0.0f;
	m_boxBody.fixtureDef.restitution = 0.0f;

	// Ground
	m_groundBody.bodyDef.type = b2_staticBody;

	// Serialization
	m_groundBody.fixtureDef.userData.pointer = Ground;
	
	m_groundBody.fixtureDef.shape = &m_groundShape;
	m_groundBody.fixtureDef.density = 0.2f;
	m_groundBody.fixtureDef.friction = 0.1f;
	m_groundBody.fixtureDef.restitution = 0.0f;

	// Plank
	m_plankBody.bodyDef.type = b2_dynamicBody;

	// Serialization
	m_plankBody.fixtureDef.userData.pointer = Plank;
	
	m_plankBody.fixtureDef.shape = &m_plankShape;
	m_plankBody.fixtureDef.density = 0.0f;
	m_plankBody.fixtureDef.friction = 0.0f;
	m_plankBody.fixtureDef.restitution = 0.0f;

	// Triangle
	m_triangleBody.bodyDef.type = b2_dynamicBody;

	// Serialization
	m_triangleBody.fixtureDef.userData.pointer = Triangle;
	
	m_triangleBody.fixtureDef.shape = &m_triangleShape;
	m_triangleBody.fixtureDef.density = 0.0f;
	m_triangleBody.fixtureDef.friction = 0.0f;
	m_triangleBody.fixtureDef.restitution = 0.0f;

	// Circle
	m_circleBody.bodyDef.type = b2_dynamicBody;
	m_circleBody.bodyDef.gravityScale = 0;

	// Serialization
	m_circleBody.fixtureDef.userData.pointer = Circle;
	
	m_circleBody.fixtureDef.shape = &m_circleShape;
	m_circleBody.fixtureDef.density = 3.f;
	m_circleBody.fixtureDef.friction = 0.5f;
	m_circleBody.fixtureDef.restitution = 0.2f;
	
	
}

b2Shape* Box2dDatabase::fromTypeToShape(DatabaseShapeTypes type) {
	switch(type) {
	case Box:
		return &m_boxShape;
	case Circle:
		return &m_circleShape;
	case Triangle:
		return &m_triangleShape;
	case Plank:
		return &m_plankShape;
	case Ground:
		return &m_groundShape;
	default:
		return nullptr;
	}
}

Box2dDatabase& Box2dDatabase::getInstance() {
	static Box2dDatabase b2ddb;
	return b2ddb;
}
