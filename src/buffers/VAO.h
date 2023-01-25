#pragma once
#include <glad/glad.h>

class VAO
{
public:
    unsigned int vao;
	VAO();
	~VAO();
	void attribPointer(int slot, int numberElements, int typedata, int step, int begin); //step - numb* sizeof(float), begin - numb*sizeof(float)
	void bind();
};