//
// Created by Viktor on 17.2.2021 г..
//

#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "GL/glew.h"

class VertexArray {
private:
public:
	unsigned int arrayObject;
	bool m_isRaii;
public:
	VertexArray(bool isRaii = true);
	VertexArray(const VertexArray& other) = default;
	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(const VertexArray& other) = default;
	~VertexArray();
public:
	void initialize();
	void free();
	void bind() const;
	static void unbind();
};


#endif //VERTEX_ARRAY_H
