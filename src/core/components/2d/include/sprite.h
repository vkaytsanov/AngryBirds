#pragma once
#include "entityx/Entity.h"
#include "utils/geometry/include/vector2.h"
#include "utils/geometry/include/vector3.h"
#include "utils/include/texture_region.h"
#include "utils/openGL/include/vertex_array.h"

#define SPRITE_DESCALE 15

struct Vertex2d {
	Vector2f position;
	Vector2f uvs;

	Vertex2d(const Vector2f& pos, const Vector2f& uv) : position(pos), uvs(uv) {
	}
};

class Sprite : public entityx::Component<Sprite> {
private:
	VertexArray m_vao;
private:
	void init();
public:
	TextureRegion m_textureRegion;
	Vector3f m_color;
	bool m_flipX = false;
	bool m_flipY = false;
public:
	Sprite() = default;
	Sprite(const TextureRegion& tR, bool hasAnimator = false);
	Sprite(Sprite&& other) = default;
	Sprite(const Sprite& other) = default;
	Sprite& operator=(Sprite&& other) = default;
	~Sprite() = default;
public:
	VertexArray* getVao();
	void setVao(VertexArray* vao);

	template <typename Archive>
	inline void save(Archive& archive) const;

	template <typename Archive>
	inline void load(Archive& archive);

};

template <typename Archive>
void Sprite::save(Archive& archive) const {
	archive(m_textureRegion, m_color, m_flipX, m_flipY);
}

template <typename Archive>
void Sprite::load(Archive& archive) {
	archive(m_textureRegion, m_color, m_flipX, m_flipY);
	init();
}
