#pragma once
#include <glad/glad.h>
#include <iostream>

class Texture
{

public:
	unsigned int texture;

	Texture();
	~Texture();
	void setData(int internalFormat, int dataFormat, int chanalFormat, int width, int height, void* data);
	void activeTexture(int textureId);
	void bind();
	void unbind();

};