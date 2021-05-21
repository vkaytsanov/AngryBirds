#include "include/box2d_database.h"

#include "include/lib.h"

void Box2dDatabase::createShapes() {
	m_boxShape.SetAsBox(5, 5);
	{
		b2Vec2 vertices[3] = {
			{-5, -5},
			{5, -5},
			{0, 5}
		};
		m_triangleShape.Set(vertices, 3);
	}
	m_plankShape.SetAsBox(10, 2);

	m_circleShape.m_radius = 5.f;
	m_redShape.m_radius = 2.5f;
	
	m_groundShape.SetAsBox(200, 20);

	{
		b2Vec2 vertices[3] = {
			{-3, -3.5},
			{4, -3.5},
			{0, 3}
		};
		m_chuckShape.Set(vertices, 3);
	}

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
	m_groundBody.bodyDef.linearDamping = 1;

	// Serialization
	m_groundBody.fixtureDef.userData.pointer = Ground;

	m_groundBody.fixtureDef.shape = &m_groundShape;
	m_groundBody.fixtureDef.density = 150.2f;
	m_groundBody.fixtureDef.friction = 150.1f;
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

	// Terence
	m_terenceBody.entityType = Terence;
	m_terenceBody.bodyDef.type = b2_dynamicBody;
	m_terenceBody.bodyDef.gravityScale = 0;

	m_terenceBody.bodyDef.linearDamping = 0.2f;
	m_terenceBody.fixtureDef.shape = &m_circleShape;
	m_terenceBody.fixtureDef.density = 3.f;
	m_terenceBody.fixtureDef.friction = 0.5f;
	m_terenceBody.fixtureDef.restitution = 0.2f;


	// Chuck
	m_chuckBody.entityType = Chuck;
	m_chuckBody.bodyDef.type = b2_dynamicBody;
	m_chuckBody.bodyDef.gravityScale = 0;

	m_chuckBody.bodyDef.linearDamping = 0.2f;
	m_chuckBody.fixtureDef.shape = &m_chuckShape;
	m_chuckBody.fixtureDef.density = 3.f;
	m_chuckBody.fixtureDef.friction = 0.5f;
	m_chuckBody.fixtureDef.restitution = 0.2f;
	
	m_redBody.entityType = Red;
	m_redBody.bodyDef.type = b2_dynamicBody;
	m_redBody.bodyDef.gravityScale = 0;

	m_redBody.bodyDef.linearDamping = 0.2f;
	m_redBody.fixtureDef.shape = &m_redShape;
	m_redBody.fixtureDef.density = 3.f;
	m_redBody.fixtureDef.friction = 0.5f;
	m_redBody.fixtureDef.restitution = 0.2f;

}

b2Shape* Box2dDatabase::fromTypeToShape(DatabaseShapeTypes type) {
	switch (type) {
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
	}
	return nullptr;
}

BodyInfo& Box2dDatabase::fromTypeToBody(EntityType type) {
	switch (type) {
		case PigMinion:
		case Terence:
			return m_terenceBody;
		case Chuck:
			return m_chuckBody;
		case Red:
			return m_redBody;
		default:
			Lib::app->error("Box2dDatabase", "couldn't deserialize type");
			return m_terenceBody;
	}
}

Box2dDatabase& Box2dDatabase::getInstance() {
	static Box2dDatabase b2ddb;
	return b2ddb;
}
