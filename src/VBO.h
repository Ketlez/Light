#pragma once
#include <glad/glad.h>

class VBO
{
public:
	unsigned int vbo;
	VBO();
	~VBO();
	void bind();
	void unBind();
	void setData(void* data, int nBytes);

};