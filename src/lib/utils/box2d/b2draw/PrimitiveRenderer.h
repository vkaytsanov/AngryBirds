#ifndef HEADER_INCLUDE__RECURSION__PHYSICS__B2__PRIMITIVERENDERER__H
#define HEADER_INCLUDE__RECURSION__PHYSICS__B2__PRIMITIVERENDERER__H


#if !defined(__EMSCRIPTEN__)
#include "GL/glew.h"
#else
#include "emscripten.h"
#include <GLES3/gl3.h>
#endif

#include <vector>
#include <utility>

#include "box2d-emscripten/Common/b2Draw.h"

#include "utils/include/shaders.h"
#include "utils/openGL/include/vertex_array.h"
#include "utils/openGL/include/vertex_buffer.h"


namespace b2draw {


	using Vertex = std::pair<b2Vec2, b2Color>;


	class PrimitiveRenderer {
	public:
		/**
		 * Create an uninitialised PrimitiveRenderer.
		 *
		 * If using this constructor, make sure to call @ref
		 * setPositionAttribLocation and @ref setColourAttribLocation before
		 * attempting to render.
		 */
		inline PrimitiveRenderer(unsigned numCircleSegments = 16u)
			: PrimitiveRenderer(-1, -1, numCircleSegments) {
		}

		PrimitiveRenderer(
			GLint vertexAttribLocation,
			GLint colourAttribLocation,
			unsigned numCircleSegments = 16u
		);

		// PrimitiveRenderer is non-copyable.
		PrimitiveRenderer(PrimitiveRenderer const&) = delete;
		PrimitiveRenderer& operator=(PrimitiveRenderer const&) = delete;

		PrimitiveRenderer(PrimitiveRenderer&&) noexcept;
		PrimitiveRenderer& operator=(PrimitiveRenderer&&) noexcept;

		~PrimitiveRenderer() noexcept;

		void addPolygon(
			b2Vec2 const* pCoords,
			int32 numCoords,
			b2Color const& colour
		);

		void addCircle(
			b2Vec2 const& centre,
			float32 const radius,
			b2Color const& colour,
			float32 const initialAngle = 0.0f
		);

		void addSegment(
			b2Vec2 const& begin,
			b2Vec2 const& end,
			b2Color const& colour
		);

		/** Buffer data. */
		void bufferData();

		/** Render data. */
		void render(GLenum const mode);

		/**
		 * Clear internally buffered data.
		 *
		 * Should be called after every b2World::DrawDebugData call.
		 */
		void clear();

		inline std::size_t const numCircleSegments() const noexcept { return m_tmpCircleBuffer.size(); }

		inline std::size_t vertexCount() const noexcept { return m_vertices.size(); }

		inline std::size_t polygonCount() const noexcept { return m_polygonSizes.size(); }

		inline bool empty() const noexcept { return m_firstIndices.empty(); }

		/** Set the number of circle segments. */
		void setCircleSegments(unsigned count);

		/** Set the position attribute location. */
		inline void
		setPositionAttribLocation(GLint location) noexcept {
			m_vao.bind();
			m_vbo.bind();
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(
				location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		}

		/** Set the colour attribute location. */
		inline void
		setColourAttribLocation(GLint location) noexcept {
			m_vao.bind();
			m_vbo.bind();
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(
				location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
				reinterpret_cast<void const*>(offsetof(Vertex, second)));
		}

		inline void
		setAttribLocations(GLint positionLocation, GLint colourLocation) noexcept {
			m_vao.bind();
			m_vbo.bind();

			glEnableVertexAttribArray(positionLocation);
			glVertexAttribPointer(
				positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

			glEnableVertexAttribArray(colourLocation);
			glVertexAttribPointer(
				colourLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
				reinterpret_cast<void const*>(offsetof(Vertex, second)));
		}

	private:
		std::vector<Vertex> m_vertices;
		std::vector<GLint> m_firstIndices;
		std::vector<GLsizei> m_polygonSizes;
		std::vector<b2Vec2> m_tmpCircleBuffer;

		VertexBuffer m_vbo;
		VertexArray m_vao;
	};


} // namespace b2draw
#endif // #ifndef HEADER_INCLUDE__RECURSION__PHYSICS__B2__PRIMITIVERENDERER__H
