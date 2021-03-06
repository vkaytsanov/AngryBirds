#include "include/sprite.h"

#include "utils/geometry/include/vector2.h"
#include "utils/openGL/include/index_buffer.h"
#include "utils/openGL/include/vertex_buffer.h"

void Sprite::init() {
	static bool indexBufferInitialized = false;
	static IndexBuffer ibo;
	if (!indexBufferInitialized) {
		indexBufferInitialized = true;
		GLuint indices[6] = {
			0, 1, 2,
			2, 3, 0
		};
		ibo.bind();
		ibo.bufferData(6 * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	const float width = static_cast<float>(m_textureRegion.getRegionWidth()) / SPRITE_DESCALE;
	const float height = static_cast<float>(m_textureRegion.getRegionHeight()) / SPRITE_DESCALE;
	const float u = m_textureRegion.getU();
	const float v = m_textureRegion.getV();
	const float u2 = m_textureRegion.getU2();
	const float v2 = m_textureRegion.getV2();
	
	Vertex2d vertices[] = {
		Vertex2d(Vector2f(-width, -height), Vector2f(u, v2 * m_textureRegion.m_tilingY)),
		Vertex2d(Vector2f(width, -height), Vector2f(u2 * m_textureRegion.m_tilingX, v2 * m_textureRegion.m_tilingY)),
		Vertex2d(Vector2f(width, height), Vector2f(u2 * m_textureRegion.m_tilingX, v)),
		Vertex2d(Vector2f(-width, height), Vector2f(u, v)),
	};

#ifdef REUSE_BUFFERS
	m_vao.initialize();
#endif
	VertexBuffer vbo;
	m_vao.bind();
	vbo.bind();
	ibo.bind();

	vbo.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (GLvoid*)offsetof(Vertex2d, position));
	vbo.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (GLvoid*)offsetof(Vertex2d, uvs));

	vbo.bufferData(sizeof(Vertex2d) * 4, vertices, GL_STATIC_DRAW);
	vbo.unbind();

	m_vao.unbind();
}

Sprite::Sprite(const TextureRegion& tR, bool hasAnimator) : m_textureRegion(tR) {
	// if the entity has animator, we don't need to generate buffer since
	// they will be overwritten by the animator
	if (!hasAnimator) {
		init();
	}
}


VertexArray* Sprite::getVao() {
	return &m_vao;
}

void Sprite::setVao(VertexArray* vao) {
	m_vao = *vao;
}
