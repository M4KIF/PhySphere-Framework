
// Custom Libraries
#include<glad/glad.h>
#include<glfw3.h>
#include<glfw3native.h>

// Default Libraries
#include<iostream>
#include<typeinfo>

// Game Files
#include<Engine/WorldCreation/Fundamental Elements/Octree.h>



int main(void)
{
    /*
    * GLFW and GLAD setup
    */

    std::cout << "Starting the GLFW context" << std::endl;

    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(1280, 720, "PhySphere Framework", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Validate the window
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Validate the context
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, 1280, 720);

    /*
    * Game parameters and variables initialisation
    */

    Collisions::AABB bb(glm::vec3(0.0f), glm::vec3(16.0f));

    Octree::Octree<int, 5> x(bb);

    Collisions::AABB aa(glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(0.0f));
    x.insert(2, aa);
    for (int i = 0; i < 5000; i++)
    {
        auto rand_float = [](const float a, const float b)
        {
            return float(rand()) / (float)RAND_MAX * (b - a) + a;
        };
        Collisions::AABB var(glm::vec3(rand_float(1.0, 2.0)), glm::vec3(rand_float(1.0, 2.0)));
        x.insert(rand(), var);
    }

    // Game Loop itself

    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render


   
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}