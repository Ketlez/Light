#include "EBO.h"

EBO::EBO()
{
	glGenBuffers(1, &ebo);
}
EBO::~EBO()
{
	glDeleteBuffers(1, &ebo);
}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void EBO::unBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::setData(void* data, int nBytes)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nBytes, data, GL_STATIC_DRAW);
}
