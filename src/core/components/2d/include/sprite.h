#pragma once
#include "entityx/Entity.h"
#include "utils/geometry/include/vector2.h"
#include "utils/geometry/include/vector3.h"
#include "utils/include/texture_region.h"
#include "utils/openGL/include/vertex_array.h"

// FIXME: dirty way to change the size of the vertices
// in case when there is a viewport
#define SPRITE_DESCALE 15

// in case there are a lot of sprites with same textures
// then its best to create a database of already initialized
// and sent to the GPU buffers, which can be massively reused.
// In that case, buffers must not use the RAII pattern and buffers
// must be manually initialized and released from their corresponding
// databases
#define REUSE_BUFFERS

struct Vertex2d {
	Vector2f position;
	Vector2f uvs;

	Vertex2d(const Vector2f& pos, const Vector2f& uv) : position(pos), uvs(uv) {
	}
};

class Sprite : public entityx::Component<Sprite> {
private:
#ifdef REUSE_BUFFERS
	VertexArray m_vao = VertexArray(false);
#else
	VertexArray m_vao;
#endif
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
	Sprite(const Sprite& other) = default;
	Sprite(Sprite&& other) = default;
	Sprite& operator=(const Sprite& other) = delete;
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
