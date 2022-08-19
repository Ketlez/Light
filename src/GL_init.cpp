#include "GL_init.h"

static void SetParameters()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

}

bool GLinit(GLFWwindow*& window, int width, int height, const char* title)
{
	if (!glfwInit())
	{
		std::cout << "glfw not init!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);


	//use MSAA
	glfwWindowHint(GLFW_SAMPLES, 64);
	

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	
	//glfwSetWindowOpacity(window, 0.2f);

	glfwMakeContextCurrent(window);

	//disable fps lock
	glfwSwapInterval(0);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	SetParameters();

    return true;
}
