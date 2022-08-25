#pragma once

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <array>
#include <tuple>
#include "LightModel.h"
#include "Texture.h"

class Surface
{
public:
    Surface();
    ~Surface();
    std::array<float, 28800> vertices;
    void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, LightCubeModel::LightModel& lightModel, const float deltaTime);
private:
    std::array<float, 28800> createSurface();
    void drawStatic();
    void bindTexture();
    Texture texture;
    Shader m_shader;
    VAO m_vao;
    VBO m_vbo;


};