#include "include/sprite.h"

#include "utils/geometry/include/vector2.h"
#include "utils/openGL/include/index_buffer.h"
#include "utils/openGL/include/vertex_buffer.h"

Sprite::Sprite(const TextureRegion& tR) : m_textureRegion(tR) {
	// std::cout << "size: " << sizeof(*this);
	// assert(sizeof(*this) % 16 == 0); // memory alignment
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
		Vertex2d(Vector2f(0, 0), Vector2f(tR.getU(), tR.getV2())),
		Vertex2d(Vector2f(200.0f, 0), Vector2f(tR.getU2(), tR.getV2())),
		Vertex2d(Vector2f(200.0f, 200), Vector2f(tR.getU2(), tR.getV())),
		Vertex2d(Vector2f(0.0f, 200), Vector2f(tR.getU(), tR.getV())),
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

const VertexArray* Sprite::getVao() const {
	return &m_vao;
}
