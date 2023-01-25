#include "VBO.h"

VBO::VBO()
{
	glGenBuffers(1, &vbo);
}
VBO::~VBO()
{
	glDeleteBuffers(1, &vbo);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setData(void* data, int nBytes)
{
	glBufferData(GL_ARRAY_BUFFER, nBytes, data, GL_STATIC_DRAW);
}
