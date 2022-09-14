#include "BlendingTexture.h"

BlendingTexture::BlendingTexture() : m_shader("VertexShaderBlendingTexture.txt", "FragmentShaderBlendingTexture.txt")
{
	bindTexture();
	
	m_vao.bind();
	m_vbo.bind();
	m_vbo.setData(defaultVertices.data(), sizeof(float) * defaultVertices.size());
	m_vao.attribPointer(0, 3, GL_FLOAT, 5 * sizeof(float), 0);
	m_vao.attribPointer(1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));
}

BlendingTexture::~BlendingTexture()
{
}

void BlendingTexture::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model)
{
	m_shader.use();
	m_vao.bind();
	texture.activeTexture(0);
	texture.bind();
	

	m_shader.setInt("texture1", 0);
	

	m_shader.setMatrix4("view", viewMatrix);
	m_shader.setMatrix4("projection", projectionMatrix);
	m_shader.setMatrix4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void BlendingTexture::bindTexture()
{
	stbi_set_flip_vertically_on_load(true);
	int wihgt, hight, nrChannels;
	unsigned char* data;

	texture.bind();
	data = stbi_load("texture/5-20220208_123941.png", &wihgt, &hight, &nrChannels, 0);
	texture.setData(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, wihgt, hight, data);
	stbi_image_free(data);

}
