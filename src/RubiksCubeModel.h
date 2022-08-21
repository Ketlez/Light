#pragma once

#include <queue>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <array>
#include <tuple>
#include "LightModel.h"
struct Color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;

	std::tuple<float, float, float> toFloat();
};
namespace ModelCube {
class ColorScheme
{
	Color front;
	Color up;
	Color back;
	Color down;
	Color right;
	Color left;

public:
	ColorScheme(Color front,
		Color up,
		Color back,
		Color down,
		Color right,
		Color left
	);

	std::array<float, 8748> createArray() const;
	std::array<float, 8748> createArrayFromOneCube(const std::array<float, 324>& oneCubeVertices) const;
	std::array<Color, 6> asArray() const;

	static ColorScheme Classic;
};



class Model
{
public:
	Model(const ColorScheme& colorSceme);
	~Model();
	std::array<float, 8748> vertices;
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, LightCubeModel::LightModel& lightModel, const float deltaTime);
private:
	void drawStatic();
	Shader m_shader;
	VAO m_vao;
	VBO m_vbo;
	
	
};
}