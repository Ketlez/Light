#include "Application.h"


void Application::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        if (fullsize)
        {
            glfwRestoreWindow(window);
            fullsize = false;

        }
        else
        {
            fullsize = true;
            glfwMaximizeWindow(window);
        }
    }

    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if (fullscreen)
        {
            glfwSetWindowMonitor(window, NULL, 200, 200, 800, 600, GLFW_DONT_CARE);
            fullscreen = false;
            glfwRestoreWindow(window);
            fullsize = false;
        }
        else
        {
            int w, h;
            int x, y;
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
            //const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, x, y, w, h, GLFW_DONT_CARE);//mode->refreshRate);
            fullscreen = true;
        }
    }
}

void Application::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);

}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Application::SetCallbackFunctions(GLFWwindow* window)
{
    Application* myPtr = this;
    glfwSetWindowUserPointer(window, myPtr);

    auto KeyCallback = [](GLFWwindow* w, int a, int b, int c, int d)
    {
        static_cast<Application*>(glfwGetWindowUserPointer(w))->key_callback(w, a, b, c, d);
    };
    glfwSetKeyCallback(window, KeyCallback);

    //Bind Cursor func
    auto ScrollCallback = [](GLFWwindow* w, double a, double b)
    {
        static_cast<Application*>(glfwGetWindowUserPointer(w))->scroll_callback(w, a, b);
    };
    glfwSetScrollCallback(window, ScrollCallback);

    //Bind Mouse func
    auto FramebufferSizeCallback = [](GLFWwindow* w, int a, int b)
    {
        static_cast<Application*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, a, b);
    };
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    auto MouseCallback = [](GLFWwindow* w, double a, double b)
    {
        static_cast<Application*>(glfwGetWindowUserPointer(w))->mouse_callback(w, a, b);
    };
    glfwSetCursorPosCallback(window, MouseCallback);
}

Application::Application(): window(NULL)
{
	if (!GLinit(window, SCR_WIDTH, SCR_HEIGHT))
	{
		return;
	}

    SetCallbackFunctions(window);
}


void Application::launchApp()
{
    int w, h;

    //RubiksCube::ColorScheme Scheme;
    //RubiksCube::Model cube(RubiksCube::ColorScheme());
    ModelCube::Model cube(ModelCube::ColorScheme::Classic);
    LightCubeModel::LightModel lightCube(glm::vec3(1.0f));

    glm::vec3 lightPos(5.5f, 0.f, 0.f);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);


        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        //glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetWindowSize(window, &w, &h);
        if (h == 0)
            h = 1;


        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)w / (float)(h), 0.01f, 100.0f);
        //glm::mat4 projection = glm::mat4(1.0f);

        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::rotate(lightModel, float(glfwGetTime())*2.f, glm::vec3(0, 1, 0));
        glm::vec4 lightPosRotate = lightModel * glm::vec4(lightPos, 1.f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.5, 0.5, 0.5));

        //lightCube.lightColor.x = sin(glfwGetTime());
        //lightCube.lightColor.z = 1-sin(glfwGetTime());
        //lightCube.lightColor.y = cos(glfwGetTime());
        lightCube.cameraPos = camera.Position;
        lightCube.pos = lightPosRotate;

        lightCube.draw(view, projection, lightModel, deltaTime);

        
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, float(glfwGetTime()), glm::vec3(0, 1, 0));

        cube.draw(view, projection, model, lightCube, deltaTime);

        


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
