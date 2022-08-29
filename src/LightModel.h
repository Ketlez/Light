#pragma once

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <array>

namespace LightCubeModel {
class DirLightModel
{
public:
	DirLightModel();
	~DirLightModel();
	glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f);
	glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	bool drawFlag = true;
	void updataPhong();
};

class PointLightModel
{
public:
	PointLightModel();
	~PointLightModel();
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, const float deltaTime);
	std::array<float, 108> vertices;
	glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 pos = glm::vec4(0.f, 0.f, 0.f, 0.f);
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	
	float constant = 1.f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	void updataPhong();

private:
	Shader l_shader;
	VAO l_vao;
	VBO l_vbo;
};

class SpotLightModel
{
public:
	SpotLightModel();
	~SpotLightModel();
	
	glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant = 1.f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	glm::vec3  position;
	glm::vec3  direction;
	float cutOff = glm::cos(glm::radians(12.5f));
	float outerCutOff = glm::cos(glm::radians(15.f));

	bool drawFlag = true;
	void updataPhong();
};
}