#pragma once
#include "entityx/Entity.h"
#include "utils/geometry/include/vector2.h"
#include "utils/geometry/include/vector3.h"
#include "utils/include/texture_region.h"
#include "utils/openGL/include/vertex_array.h"

struct Vertex2d {
	Vector2f position;
	Vector2f uvs;

	Vertex2d(const Vector2f& pos, const Vector2f& uv) : position(pos), uvs(uv) {
	}
};

class Sprite : public entityx::Component<Sprite> {
private:
	VertexArray m_vao;
public:
	TextureRegion m_textureRegion;
	Vector3f m_color;
	bool m_flipX;
	bool m_flipY;
public:
	Sprite(const TextureRegion& tR);
	const VertexArray* getVao() const;
};
