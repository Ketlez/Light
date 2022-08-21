#pragma once

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <array>

namespace LightCubeModel {
class LightModel
{
public:
	LightModel(glm::vec3 lightColor);
	~LightModel();
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, const float deltaTime);
	std::array<float, 108> vertices;
	glm::vec3 lightPos;
	glm::vec3 lightColor;
private:
	Shader l_shader;
	VAO l_vao;
	VBO l_vbo;
};
}