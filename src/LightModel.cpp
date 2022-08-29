#include "LightModel.h"

// DirLightModel
LightCubeModel::DirLightModel::DirLightModel()
{
	updataPhong();
}

LightCubeModel::DirLightModel::~DirLightModel(){}

void LightCubeModel::DirLightModel::updataPhong()
{
	diffuse = color * glm::vec3(0.4f);
	ambient = color * glm::vec3(0.05f);
	specular = color * glm::vec3(0.5f);
}

// PointLightModel
LightCubeModel::PointLightModel::PointLightModel(): l_shader("LightVertexShader.txt", "LightFragmentShader.txt")
{
	vertices = {
		-0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f,  0.5f, -0.5f,

	   -0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f, -0.5f, -0.5f,

	   -0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,
	   -0.5f, -0.5f,  0.5f,

	   -0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
	};
	l_vao.bind();
	l_vbo.bind();
	l_vbo.setData(vertices.data(), sizeof(float) * vertices.size());
	l_vao.attribPointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);
	updataPhong();
}

LightCubeModel::PointLightModel::~PointLightModel(){}

void LightCubeModel::PointLightModel::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, const float deltaTime)
{
	l_shader.use();
	l_vao.bind();

	l_shader.setMatrix4("view", viewMatrix);
	l_shader.setMatrix4("projection", projectionMatrix);
	l_shader.setMatrix4("model", model);

	l_shader.setVec3("lightColor", color);

	updataPhong();
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightCubeModel::PointLightModel::updataPhong()
{
	diffuse = color * glm::vec3(0.8f);
	ambient = color * glm::vec3(0.05f);
	specular = color * glm::vec3(1.f);
}

// SpotLightModel
LightCubeModel::SpotLightModel::SpotLightModel()
{
	updataPhong();
}

LightCubeModel::SpotLightModel::~SpotLightModel(){}

void LightCubeModel::SpotLightModel::updataPhong()
{
	diffuse = color * glm::vec3(1.f);
	ambient = color * glm::vec3(0.f);
	specular = color * glm::vec3(1.f);
}