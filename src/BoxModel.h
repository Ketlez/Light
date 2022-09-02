#pragma once

#include <queue>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <array>
#include "LightModel.h"
#include "Texture.h"
#include <vector>




namespace ModelCube {

class Model
{
public:
	Model(const float* vertices, int size);
	~Model();
    const static std::array<float, 288> defaultVertices;
	void draw(
        glm::mat4 viewMatrix, 
        glm::mat4 projectionMatrix, 
        glm::mat4 model, 
        LightCubeModel::DirLightModel& Dirlight, 
        LightCubeModel::PointLightModel* Pointlight,
        int numberPointLight,
        LightCubeModel::SpotLightModel& Spotlight,
        glm::vec3 cameraPos,
        const float deltaTime,
        bool stencil
    );
private:
    int sizeVertices;
    void bindDirlight(LightCubeModel::DirLightModel& Dirlight);
    void bindPointlight(LightCubeModel::PointLightModel* Pointlight, int i);
    void bindSpotlight(LightCubeModel::SpotLightModel& Spotlight);
	void drawStatic();
	void bindTexture();
	Texture textureDiffuse;
	Texture textureSpecular;
	Shader m_shader;
	VAO m_vao;
	VBO m_vbo;
    
};
}