#include "BoxModel.h"
#include <vector>
ModelCube::Model::Model(const float* vertices, int size)
	: m_shader("FvertexShader.txt", "FfragmentShader.txt")
{
	bindTexture();
	this->sizeVertices = size / 8;
	m_vao.bind();
	m_vbo.bind();
	m_vbo.setData((void*)vertices, sizeof(float)*size);
	m_vao.attribPointer(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
	m_vao.attribPointer(1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
	m_vao.attribPointer(2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));
}

ModelCube::Model::~Model()
{
}


void ModelCube::Model::draw(
	glm::mat4 viewMatrix,
	glm::mat4 projectionMatrix,
	glm::mat4 model,
	LightCubeModel::DirLightModel& Dirlight,
	LightCubeModel::PointLightModel* Pointlight,
	int numberPointLight,
	LightCubeModel::SpotLightModel& Spotlight,
	glm::vec3 cameraPos,
	const float time
)
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

// light settings
	m_shader.setVec3("viewPos", cameraPos);
	if (Dirlight.drawFlag)
		bindDirlight(Dirlight);
	
		bindPointlight(Pointlight, numberPointLight);
	if (Spotlight.drawFlag)
		bindSpotlight(Spotlight);

	drawStatic();
}

void ModelCube::Model::bindDirlight(LightCubeModel::DirLightModel& Dirlight)
{
	Dirlight.updataPhong();
	m_shader.setVec3("dirLight.direction", Dirlight.direction);

	m_shader.setVec3("dirLight.ambient", Dirlight.ambient);
	m_shader.setVec3("dirLight.diffuse", Dirlight.diffuse);
	m_shader.setVec3("dirLight.specular", Dirlight.specular);

	m_shader.setBool("dirLight.drawFlag", Dirlight.drawFlag);
}

void ModelCube::Model::bindPointlight(LightCubeModel::PointLightModel* Pointlight, int numberPointLight)
{
	for (int i = 0; i < numberPointLight; i++) {
		Pointlight[i].updataPhong();
		m_shader.setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].position"), Pointlight[i].pos);
													 											 
		m_shader.setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].ambient"), Pointlight[i].ambient);
		m_shader.setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].diffuse"), Pointlight[i].diffuse);
		m_shader.setVec3(std::string("pointLights[") + std::to_string(i) + std::string("].specular"), Pointlight[i].specular);

		m_shader.setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].constant"), Pointlight[i].constant);
		m_shader.setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].linear"), Pointlight[i].linear);
		m_shader.setFloat(std::string("pointLights[") + std::to_string(i) + std::string("].quadratic"), Pointlight[i].quadratic);
	}
}

void ModelCube::Model::bindSpotlight(LightCubeModel::SpotLightModel& Spotlight)
{
	Spotlight.updataPhong();
	m_shader.setVec3("spotLight.position", Spotlight.position);
	m_shader.setVec3("spotLight.direction", Spotlight.direction);

	m_shader.setVec3("spotLight.ambient", Spotlight.ambient);
	m_shader.setVec3("spotLight.diffuse", Spotlight.diffuse);
	m_shader.setVec3("spotLight.specular", Spotlight.specular);

	m_shader.setFloat("spotLight.constant", Spotlight.constant);
	m_shader.setFloat("spotLight.linear", Spotlight.linear);
	m_shader.setFloat("spotLight.quadratic", Spotlight.quadratic);

	m_shader.setFloat("spotLight.cutOff", Spotlight.cutOff);
	m_shader.setFloat("spotLight.outerCutOff", Spotlight.outerCutOff);

	m_shader.setBool("spotLight.drawFlag", Spotlight.drawFlag);

} 

void ModelCube::Model::drawStatic()
{
	
	glDrawArrays(GL_TRIANGLES, 0, sizeVertices);
}

void ModelCube::Model::bindTexture()
{
	
	//stbi_set_flip_vertically_on_load(true);
	int wihgt, hight, nrChannels;
	unsigned char* data;

	textureDiffuse.bind();
	data = stbi_load("texture/diffuse.jpg", &wihgt, &hight, &nrChannels, 0);
	textureDiffuse.setData(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, wihgt, hight, data);
	stbi_image_free(data);

	textureSpecular.bind();
	data = stbi_load("texture/specular.jpg", &wihgt, &hight, &nrChannels, 0);
	textureDiffuse.setData(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, wihgt, hight, data);
	stbi_image_free(data);
}

const std::array<float, 288> ModelCube::Model::defaultVertices = {
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
};