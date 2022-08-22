#include "BoxModel.h"
#include <vector>
ModelCube::Model::Model()
	: m_shader("FvertexShader.txt", "FfragmentShader.txt")
{
	bindTexture();

	m_vao.bind();
	m_vbo.bind();
	m_vbo.setData(vertices.data(), sizeof(float)*vertices.size());
	m_vao.attribPointer(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
	m_vao.attribPointer(1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
	m_vao.attribPointer(2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));
}

ModelCube::Model::~Model()
{
}


void ModelCube::Model::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, LightCubeModel::LightModel& lightModel, const float time)
{
	m_shader.use();
	m_vao.bind();
	textureDiffuse.activeTexture(0);
	textureDiffuse.bind();
	textureSpecular.activeTexture(1);
	textureSpecular.bind();

	m_shader.setInt("material.diffuse", 0);
	m_shader.setInt("material.specular", 1);
	m_shader.setFloat("material.shininess", 64);


	m_shader.setFloat("time", time);

	m_shader.setMatrix4("view", viewMatrix);
	m_shader.setMatrix4("projection", projectionMatrix);
	m_shader.setMatrix4("model", model);

	glm::mat3 Normal = glm::mat3(transpose(inverse(model)));
	m_shader.setMatrix3("normalModel", Normal);

	lightModel.updataPhong();
	m_shader.setVec3("light.ambient", lightModel.ambient);
	m_shader.setVec3("light.diffuse", lightModel.diffuse);
	m_shader.setVec3("light.specular", lightModel.specular);
	m_shader.setVec3("light.position", lightModel.pos);
	m_shader.setVec3("light.cameraPos", lightModel.cameraPos);


	drawStatic();
}

void ModelCube::Model::drawStatic()
{
	
	glDrawArrays(GL_TRIANGLES, 0, 972);
}

void ModelCube::Model::bindTexture()
{
	
	stbi_set_flip_vertically_on_load(true);
	int wihgt, hight, nrChannels;
	unsigned char* data;

	textureDiffuse.bind();
	data = stbi_load("texture/container2.png", &wihgt, &hight, &nrChannels, 0);
	textureDiffuse.setData(GL_RGB, GL_RGBA, GL_UNSIGNED_BYTE, wihgt, hight, data);
	stbi_image_free(data);

	textureSpecular.bind();
	data = stbi_load("texture/container2_specular.png", &wihgt, &hight, &nrChannels, 0);
	textureDiffuse.setData(GL_RGB, GL_RGBA, GL_UNSIGNED_BYTE, wihgt, hight, data);
	stbi_image_free(data);
}
