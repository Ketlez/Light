#pragma once

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <array>

namespace LightCubeModel {
class LightModel
{
public:
	LightModel();
	~LightModel();
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, glm::vec3 lightColor, const float deltaTime);
	std::array<float, 108> vertices;
private:
	Shader l_shader;
	VAO l_vao;
	VBO l_vbo;
};
}