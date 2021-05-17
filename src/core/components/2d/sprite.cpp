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
	Vertex2d vertices[] = {
		Vertex2d(Vector2f(-5, -5), Vector2f(m_textureRegion.getU(), m_textureRegion.getV2())),
		Vertex2d(Vector2f(5, -5), Vector2f(m_textureRegion.getU2(), m_textureRegion.getV2())),
		Vertex2d(Vector2f(5, 5), Vector2f(m_textureRegion.getU2(), m_textureRegion.getV())),
		Vertex2d(Vector2f(-5, 5), Vector2f(m_textureRegion.getU(), m_textureRegion.getV())),
	};

	VertexBuffer vbo;
	m_vao.bind();
	vbo.bind();
	ibo.bind();
	vbo.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (GLvoid*)offsetof(Vertex2d, position));
	vbo.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (GLvoid*)offsetof(Vertex2d, uvs));

	vbo.bind();
	vbo.bufferData(sizeof(Vertex2d) * 4, vertices, GL_STATIC_DRAW);

	m_vao.unbind();
}

Sprite::Sprite(const TextureRegion& tR) : m_textureRegion(tR) {
	// std::cout << "size: " << sizeof(*this);
	// assert(sizeof(*this) % 16 == 0); // memory alignment

	init();

}


Sprite::Sprite(Sprite&& other) noexcept {
	std::swap(m_vao, other.m_vao);
	std::swap(m_textureRegion, other.m_textureRegion);
	std::swap(m_color, other.m_color);
	std::swap(m_flipX, other.m_flipX);
	std::swap(m_flipY, other.m_flipY);
	// unsigned int tmp = other.m_vao.arrayObject;
	// other.m_vao.arrayObject = m_vao.arrayObject;
	// m_vao.arrayObject = tmp;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept{
	unsigned int tmp = other.m_vao.arrayObject;
	other.m_vao.arrayObject = m_vao.arrayObject;
	m_vao.arrayObject = tmp;
	return *this;
}

const VertexArray* Sprite::getVao() const {
	return &m_vao;
}

