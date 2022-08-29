#include "Application.h"
#include <limits>

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
        model = glm::translate(model, glm::vec3(sin(currentFrame), 0, 0));
        //model = glm::scale(model, glm::vec3(5, 5, 5));
        collisionsResolve(model);
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

void Application::collisionsResolve(const glm::mat4& model)
{
    glm::vec3 cubeMax(0.5f, 0.5f, 0.5f);
    glm::vec3 cubeMin(-0.5f, -0.5f, -0.5f);
    glm::vec3 Max = glm::vec3(model * glm::vec4(cubeMax, 1.f));
    glm::vec3 Min = glm::vec3(model * glm::vec4(cubeMin, 1.f));
    float clampX = glm::clamp(camera.Position.x, Min.x, Max.x);
    float clampY = glm::clamp(camera.Position.y, Min.y, Max.y);
    float clampZ = glm::clamp(camera.Position.z, Min.z, Max.z);

    glm::vec3 clampXYZ(clampX, clampY, clampZ);

    glm::vec3 vecRadius = clampXYZ - camera.Position;
    float radiusLength = glm::length(vecRadius);
    glm::vec3 oldCameraPos(camera.Position);
    if (radiusLength < radius)
    {
        std::vector<int> resolveDim;
        std::vector<bool> resolveIsPositive;
        resolveDim.reserve(3);
        resolveIsPositive.reserve(3);
       // constexpr float epsilon = 1e-5f;
        for (int j = 0; j < 3; j++)
        {
            
            glm::vec3 center = (Max + Min) * 0.5f;
            glm::vec3 dir = camera.Position - center;
            int dim = 0;
            float mindist = std::numeric_limits<float>::max();
            for (int i = 0; i < 3; i++)
            {
                if (!(camera.Position[i]<Max[i] && camera.Position[i]>Min[i]) && (std::abs(dir[i])< mindist))
                {
                    mindist = std::abs(dir[i]);
                    dim = i;

                }

            }
            float result = dir[dim] > 0.f ? Max[dim] + radius : Min[dim] - radius;
            if (camera.Position[dim] != result)
            {
                resolveDim.push_back(dim);
                resolveIsPositive.push_back(dir[dim] > 0.f);
            }
            camera.Position[dim] = result;
            
        }
        if (resolveDim.size() == 1)
        {
           // camera.Position[resolveDim[0]] += (resolveIsPositive[0] ? epsilon : -epsilon);
            return;

        }
        if (resolveDim.size() == 2)
        {
            glm::vec3 edge(0.f);
            int dim1 = resolveDim[0];
            int dim2 = resolveDim[1];
            edge[dim1] = resolveIsPositive[0] ? Max[dim1] : Min[dim1];
            edge[dim2] = resolveIsPositive[1] ? Max[dim2] : Min[dim2];
 
            glm::vec3 cameraPos(0.f);
            cameraPos[dim1] = oldCameraPos[dim1];
            cameraPos[dim2] = oldCameraPos[dim2];
            glm::vec3 dir = glm::normalize(cameraPos - edge);
            int dim3 = 3 - (dim1 + dim2);
            
            edge[dim3] = oldCameraPos[dim3];
           
            camera.Position = edge + dir * radius;
        }
        if (resolveDim.size() == 3)
        {
            glm::vec3 edge(0.f);
            int dim1 = resolveDim[0];
            int dim2 = resolveDim[1];
            int dim3 = resolveDim[2];
            edge[dim1] = resolveIsPositive[0] ? Max[dim1] : Min[dim1];
            edge[dim2] = resolveIsPositive[1] ? Max[dim2] : Min[dim2];
            edge[dim3] = resolveIsPositive[2] ? Max[dim3] : Min[dim3];

            glm::vec3 cameraPos(0.f);
            cameraPos[dim1] = oldCameraPos[dim1];
            cameraPos[dim2] = oldCameraPos[dim2];
            cameraPos[dim3] = oldCameraPos[dim3];
            glm::vec3 dir = glm::normalize(cameraPos - edge);

            camera.Position = edge + dir * radius;
        }
    }
}
