#include "LightModel.h"

LightCubeModel::LightModel::LightModel(): l_shader("LightVertexShader.txt", "LightFragmentShader.txt")
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
}

LightCubeModel::LightModel::~LightModel()
{
}

void LightCubeModel::LightModel::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, glm::vec3 lightColor, const float deltaTime)
{
	l_shader.use();
	l_vao.bind();

	l_shader.setMatrix("view", viewMatrix);
	l_shader.setMatrix("projection", projectionMatrix);
	l_shader.setMatrix("model", model);

	l_shader.setVec3("lightColor", lightColor);


	glDrawArrays(GL_TRIANGLES, 0, 36);
}
