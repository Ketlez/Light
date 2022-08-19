#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}
VAO::~VAO()
{
	glDeleteVertexArrays(1, &vao);
}

void VAO::attribPointer(int slot, int numberElements, int typedata, int step, int begin)
{
    glVertexAttribPointer(slot, numberElements, typedata, GL_FALSE, step, (void*)begin);
    glEnableVertexAttribArray(slot);
}



void VAO::bind()
{
    glBindVertexArray(vao);
}
