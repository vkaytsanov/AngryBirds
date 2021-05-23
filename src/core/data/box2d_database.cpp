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
	m_plankShape.SetAsBox(13.0f, 0.7f);

	m_circleShape.m_radius = 5.f;
	m_redShape.m_radius = 2.5f;
	
	m_groundShape.SetAsBox(200, 22);

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

	// birds
	for(int i = Terence; i < PigMinion; i++) {
		m_bodies[i].bodyDef.type = b2_dynamicBody;
		m_bodies[i].bodyDef.linearDamping = 0.2f;
		m_bodies[i].bodyDef.gravityScale = 0.0f;
		m_bodies[i].fixtureDef.density = 3.f;
		m_bodies[i].fixtureDef.friction = 0.5f;
		m_bodies[i].fixtureDef.restitution = 0.2f;
	}
	m_bodies[Terence].fixtureDef.shape = &m_circleShape;
	m_bodies[Red].fixtureDef.shape = &m_redShape;
	m_bodies[Chuck].fixtureDef.shape = &m_chuckShape;
	
	// Pigs
	for(int i = PigMinion; i < WoodTriangle; i++) {
		m_bodies[i].bodyDef.type = b2_dynamicBody;
		m_bodies[i].bodyDef.linearDamping = 0.0f;
		m_bodies[i].bodyDef.gravityScale = 1.0f;
		m_bodies[i].fixtureDef.shape = &m_circleShape;
		m_bodies[i].fixtureDef.density = 3.f;
		m_bodies[i].fixtureDef.friction = 0.5f;
		m_bodies[i].fixtureDef.restitution = 0.2f;
	}

	// Obstacles
	for(int i = WoodTriangle; i < ENTITY_TYPE_SIZE; i++) {
		m_bodies[i].bodyDef.type = b2_dynamicBody;
		m_bodies[i].fixtureDef.density = 0.2f;
		m_bodies[i].fixtureDef.friction = 0.2f;
		m_bodies[i].fixtureDef.restitution = 0.0f;
	}

	m_bodies[WoodTriangle].fixtureDef.shape = &m_triangleShape;
	m_bodies[WoodSquare].fixtureDef.shape = &m_boxShape;
	m_bodies[WoodRectangle].fixtureDef.shape = &m_plankShape;

	// Ground
	m_groundBody.bodyDef.type = b2_staticBody;
	m_groundBody.bodyDef.linearDamping = 1;

	m_groundBody.fixtureDef.shape = &m_groundShape;
	m_groundBody.fixtureDef.density = 150.0f;
	m_groundBody.fixtureDef.friction = 150.0f;
	m_groundBody.fixtureDef.restitution = 0.0f;
}

BodyInfo& Box2dDatabase::fromTypeToBody(EntityType type) {
	return m_bodies[type];
}

Box2dDatabase& Box2dDatabase::getInstance() {
	static Box2dDatabase b2ddb;
	return b2ddb;
}
