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
    void draw(
        glm::mat4 viewMatrix,
        glm::mat4 projectionMatrix,
        glm::mat4 model,
        LightCubeModel::DirLightModel& Dirlight,
        LightCubeModel::PointLightModel* Pointlight,
        int numberPointLight,
        LightCubeModel::SpotLightModel& Spotlight,
        glm::vec3 cameraPos,
        const float deltaTime
    );
private:
    std::array<float, 28800> createSurface();
    void bindDirlight(LightCubeModel::DirLightModel& Dirlight);
    void bindPointlight(LightCubeModel::PointLightModel* Pointlight, int i);
    void bindSpotlight(LightCubeModel::SpotLightModel& Spotlight);
    void drawStatic();
    void bindTexture();
    Texture texture;
    Shader m_shader;
    VAO m_vao;
    VBO m_vbo;


};