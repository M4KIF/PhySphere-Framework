//#pragma once

//Custom Libraries
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>
//#include<Libraries/THREADPOOL/BS_thread_pool.hpp>

//Default Libraries
#include<iostream>
#include<typeinfo>
#include<iterator>
#include<chrono>

//Game Files
#include<Spatial-Tree-Structures/Octree/Octree.h>
#include<Spatial-Tree-Structures/Octree/ContainedOctree.h>
#include<Spatial-Tree-Structures/QuadTree/QuadTree.h>



int main(void)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

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
