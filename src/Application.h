#pragma once
#include "GL_init.h"




#include "Camera.h"

#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <iostream>
#include <string>
#include <cmath>

#include <ctime>

#include "BoxModel.h"
#include "LightModel.h"
#include "Surface.h"

class Application
{
	GLFWwindow* window;

	Camera camera;

	unsigned int SCR_WIDTH = 500;
	unsigned int SCR_HEIGHT = 500;

	bool fullsize = false;
	bool fullscreen = false;

	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void SetCallbackFunctions(GLFWwindow* window);
	
public:
	Application();
	void launchApp();
};