#pragma once

#include <queue>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <array>
#include "LightModel.h"
#include "Texture.h"
#include <vector>

class BlendingTexture
{
public:
    BlendingTexture();
    ~BlendingTexture();
    std::array<float, 30> defaultVertices = 
    {
        0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  0.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  0.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  1.0f
    };
    void draw(
        glm::mat4 viewMatrix,
        glm::mat4 projectionMatrix,
        glm::mat4 model
    );
private:
    
    void bindTexture();
    Texture texture;
 
    Shader m_shader;
    VAO m_vao;
    VBO m_vbo;

};