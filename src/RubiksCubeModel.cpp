#include "RubiksCubeModel.h"
#include <vector>
ModelCube::Model::Model(const ColorScheme& colorSceme)
	: m_shader("FvertexShader.txt", "FfragmentShader.txt")
{
	vertices = colorSceme.createArray();
	m_vao.bind();
	m_vbo.bind();
	m_vbo.setData(vertices.data(), sizeof(float)*vertices.size());
	m_vao.attribPointer(0, 3, GL_FLOAT, 6 * sizeof(float), 0);
	m_vao.attribPointer(1, 3, GL_FLOAT, 6 * sizeof(float), 3 * sizeof(float));
}

ModelCube::Model::~Model()
{
}


void ModelCube::Model::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, glm::vec3 lightColor, const float deltaTime)
{
	m_shader.use();
	m_vao.bind();

	m_shader.setMatrix("view", viewMatrix);
	m_shader.setMatrix("projection", projectionMatrix);
	m_shader.setMatrix("model", model);

	m_shader.setVec3("lightColor", lightColor);


	drawStatic();
}

void ModelCube::Model::drawStatic()
{
	
	glDrawArrays(GL_TRIANGLES, 0, 972);
}

ModelCube::ColorScheme::ColorScheme(Color front, Color up, Color back, Color down, Color right, Color left)
	:front(front), up(up), back(back), down(down), right(right), left(left)
{
	
}


std::array<float, 5832> ModelCube::ColorScheme::createArray() const
{
	std::array<float, 216> verticesOneCube = {
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	};

	std::array<Color, 6> colorsArray = asArray();

	for (int i = 0; i < 6; i++)
	{
		auto [R, G, B] = colorsArray[i].toFloat();
		for (int j = 0; j < 6; j++)
		{
			verticesOneCube[i * 36 + j*6 + 3] = R;
			verticesOneCube[i * 36 + j*6 + 4] = G;
			verticesOneCube[i * 36 + j*6 + 5] = B;
		}
	}

	return createArrayFromOneCube(verticesOneCube);
}

std::array<float, 5832> ModelCube::ColorScheme::createArrayFromOneCube(const std::array<float, 216>& oneCubeVertices) const
{
	std::array<float, 5832> resultCube;
	int c = 0;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				for (int i = 0; i < 36; i++)
				{

					resultCube[c++] = oneCubeVertices[i * 6 + 0] + (x - 1);
					resultCube[c++] = oneCubeVertices[i * 6 + 1] + (y - 1);
					resultCube[c++] = oneCubeVertices[i * 6 + 2] + (z - 1);

					for (int k = 0; k < 3; k++)
					{

						resultCube[c++] = oneCubeVertices[i * 6 + 3 + k];
					}
				}
			}
		}
	}
	return resultCube;
}

std::array<Color, 6> ModelCube::ColorScheme::asArray() const
{
	std::array<Color, 6> asArray;
	asArray[0] = back;
	asArray[1] = down;
	asArray[2] = front;
	asArray[3] = left;
	asArray[4] = right;
	asArray[5] = up;
	return asArray;
}

ModelCube::ColorScheme ModelCube::ColorScheme::Classic(
	Color{ 255, 0, 0 },
	Color{ 255, 255, 255 },
	Color{ 255, 130, 0 },
	Color{ 253, 233, 16 },
	Color{ 0, 57, 110 },
	Color{ 40, 140, 51 }
	);

std::tuple<float, float, float> Color::toFloat()
{
	return std::make_tuple(R/255.f, G/255.f, B/255.f);
}
