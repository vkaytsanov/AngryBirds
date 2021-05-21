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
public:
	VertexArray();
	VertexArray(const VertexArray& other) = default;
	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(const VertexArray& other) = default;
	~VertexArray();
	void free() const;
	void bind() const;
	void unbind() const;
};


#endif //VERTEX_ARRAY_H
