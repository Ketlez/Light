#include "Surface.h"

Surface::Surface()
	: m_shader("SurfaceVertexShader.txt", "SurfaceFragmentShader.txt")
{
	bindTexture();
	vertices = createSurface();
	m_vao.bind();
	m_vbo.bind();
	m_vbo.setData(vertices.data(), sizeof(float) * vertices.size());
	m_vao.attribPointer(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
	m_vao.attribPointer(1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
	m_vao.attribPointer(2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));
}

Surface::~Surface()
{
}


void Surface::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, LightCubeModel::LightModel& lightModel, const float time)
{
	m_shader.use();
	m_vao.bind();
	texture.activeTexture(0);
	texture.bind();

	m_shader.setInt("material.diffuse", 0);
	m_shader.setFloat("material.shininess", 4);


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

std::array<float, 28800> Surface::createSurface()
{
	std::array<float, 288> verticesOneCube = {
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

	std::array<float, 28800> vertices;

	int c = 0;
	for(int x=0; x<10; x++)
		for(int z=0; z<10; z++)
			for (int i = 0; i < 36; i++) {

				vertices[c++] = verticesOneCube[i * 8 + 0] + (x - 5);
				vertices[c++] = verticesOneCube[i * 8 + 1];
				vertices[c++] = verticesOneCube[i * 8 + 2] + (z - 5);

				for(int k = 0; k < 5; k++)
					vertices[c++] = verticesOneCube[i * 8 + 3 + k];
			
			}
	return vertices;
}

void Surface::drawStatic()
{

	glDrawArrays(GL_TRIANGLES, 0, 3600);
}

void Surface::bindTexture()
{

	stbi_set_flip_vertically_on_load(true);
	int wihgt, hight, nrChannels;
	unsigned char* data;

	texture.bind();
	data = stbi_load("texture/pol.jpg", &wihgt, &hight, &nrChannels, 0);
	texture.setData(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, wihgt, hight, data);
	stbi_image_free(data);
}
