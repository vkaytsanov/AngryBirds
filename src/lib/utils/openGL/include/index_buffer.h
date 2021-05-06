//
// Created by Viktor on 17.2.2021 г..
//

#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "GL/glew.h"

class IndexBuffer {
private:
	unsigned int buffer;
public:
	IndexBuffer();
	~IndexBuffer();
	void bind();
	void bufferData(GLsizeiptr size, void* data, GLenum usage);
	void unbind();
};


#endif //INDEX_BUFFER_H
