#include "LightModel.h"

LightCubeModel::LightModel::LightModel(glm::vec3 lightColor): l_shader("LightVertexShader.txt", "LightFragmentShader.txt")
{
	this->color = lightColor;

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
}

LightCubeModel::LightModel::~LightModel()
{
}

void LightCubeModel::LightModel::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, const float deltaTime)
{
	l_shader.use();
	l_vao.bind();


	l_shader.setMatrix4("view", viewMatrix);
	l_shader.setMatrix4("projection", projectionMatrix);
	l_shader.setMatrix4("model", model);

	l_shader.setVec3("lightColor", color);


	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightCubeModel::LightModel::updataPhong()
{
	diffuse = color * glm::vec3(0.5f);
	ambient = diffuse * glm::vec3(0.2f);
	specular = color;
}
