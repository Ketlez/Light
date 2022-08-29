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
    ModelCube::Model cube;
    Surface surface;
    LightCubeModel::DirLightModel Dirlight;
    int numberPointLight = 2;
    LightCubeModel::PointLightModel Pointlight[2];
    LightCubeModel::SpotLightModel Spotlight;

    glm::vec4 PointlightPos1(-5.f, 4.f, 0.f, 1.f);
    glm::vec4 PointlightPos2(5.f, 4.f, 0.f, 1.f);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);


        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetWindowSize(window, &w, &h);
        if (h == 0)
            h = 1;


        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)w / (float)(h), 0.01f, 100.0f);

        glm::mat4 lightModel1 = glm::mat4(1.0f);
        glm::vec3 lightPosRotate1 = glm::vec3(lightModel1 * PointlightPos1);
        lightModel1 = glm::translate(lightModel1, glm::vec3(PointlightPos1));
        lightModel1 = glm::scale(lightModel1, glm::vec3(0.1, 0.1, 0.1));
        Pointlight[0].pos = lightPosRotate1;
        glm::mat4 lightModel2 = glm::mat4(1.0f);
        glm::vec3 lightPosRotate2 = glm::vec3(lightModel2 * PointlightPos2);
        lightModel2 = glm::translate(lightModel2, glm::vec3(PointlightPos2));
        lightModel2 = glm::scale(lightModel2, glm::vec3(0.1, 0.1, 0.1));
        Pointlight[1].pos = lightPosRotate2;

        
        Pointlight[0].draw(view, projection, lightModel1, deltaTime);
        Pointlight[1].draw(view, projection, lightModel2, deltaTime);

        Dirlight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
        Spotlight.position = camera.Position;
        Spotlight.direction = camera.Front;
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 1, 0));
        cube.draw(view, projection, model, Dirlight, Pointlight, numberPointLight, Spotlight, camera.Position, float(glfwGetTime()));
        
        //model = glm::translate(model, glm::vec3(4, 1, 2.5f));
        //cube.draw(view, projection, model, lightCube, float(glfwGetTime()));
        //model = glm::translate(model, glm::vec3(-2, 1, 2.5f));
        //cube.draw(view, projection, model, lightCube, float(glfwGetTime()));
        

        glm::mat4 surfaceModel = glm::mat4(1.0f);
        //surfaceModel = glm::scale(surfaceModel, glm::vec3(0.5f));
        surface.draw(view, projection, surfaceModel, Dirlight, Pointlight, numberPointLight, Spotlight, camera.Position, float(glfwGetTime()));


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
