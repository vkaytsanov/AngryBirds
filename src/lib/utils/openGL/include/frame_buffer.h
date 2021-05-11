#pragma once
#include "utils/include/texture.h"

class FrameBuffer {
private:
	unsigned int m_buffer;
	unsigned int m_textureBuffer;
	unsigned int m_renderBuffer;
public:
	FrameBuffer();
	FrameBuffer(const int width, const int height);
	~FrameBuffer();
	void bind();
	void unbind();
	void attach(std::shared_ptr<Texture> texture);
	unsigned int getTextureBuffer();

};
