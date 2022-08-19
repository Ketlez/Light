#pragma once
#include <glad/glad.h>

class EBO
{
public:
	unsigned int ebo;
	EBO();
	~EBO();
	void bind();
	void unBind();
	void setData(void* data, int nBytes);

};