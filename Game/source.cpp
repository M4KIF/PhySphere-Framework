
// Custom Libraries
#include<glad/glad.h>
#include<glfw3.h>
#include<glfw3native.h>

// Default Libraries
#include<iostream>
#include<typeinfo>
#include<iterator>

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

    Collisions::AABB chunk_position(glm::vec3(0.0f), glm::vec3(16.0f, 16.0f, -16.0f));
    Octree::Octree<int, nullptr_t, 5> chunk(chunk_position);

    glm::vec3 minimum, maximum;
    minimum = glm::vec3(0.0f);
    maximum = glm::vec3(1.0f, 1.0f, -1.0f);
    Collisions::AABB block(minimum, maximum);

    int how_much_fits = 0;

    srand((unsigned)time(NULL));

    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
            {
                block.update_position(glm::vec3((minimum.x + k), (minimum.y+i), (minimum.z-j)), glm::vec3((maximum.x + k), (maximum.y+i), (maximum.z-j)));
                std::pair<int, nullptr_t> temp;
                temp = { rand(), nullptr };
                chunk.insert(temp, block);
                if (chunk_position.contains(block)) how_much_fits++;
            }

    std::list<std::pair<int, nullptr_t>> items;
    Collisions::AABB area(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(2.0f, 2.0f, -2.0f));
    items = chunk.search(area);
    std::list<std::pair<int, nullptr_t>>::iterator it;

    if (items.empty()) std::cout << "nie\n";
    else { std::cout << "cos jest.\n"; };

    for (it = items.begin(); it!=items.end(); ++it)
    {
        std::cout << "\nWartosc 1: " << it->first << "\n";
    }

    std::cout << "Tyle naliczy³o w teorii: " << how_much_fits << "\n";

    std::cout << "\nTyle weszlo w size: " << chunk.size() << "\n";

    std::array<glm::vec3, 2> dimensions = chunk.position();

    std::cout << "Dimensions are: " << dimensions[0][0] << ", " << dimensions[0][1] << ", " << dimensions[0][2] << "\n"
        << dimensions[1][0] << ", " << dimensions[1][1] << ", " << dimensions[1][2] << "\n";

    chunk.resize(glm::vec3(16.0f, 0.0f, -16.0f), glm::vec3(32.0f, 16.0f, -32.0f));

    dimensions = chunk.position();

    std::cout << "Dimensions are: " << dimensions[0][0] << ", " << dimensions[0][1] << ", " << dimensions[0][2] << "\n"
        << dimensions[1][0] << ", " << dimensions[1][1] << ", " << dimensions[1][2] << "\n";

    minimum = dimensions[0];
    maximum = glm::vec3(dimensions[0].x+1.0f, dimensions[0].y+1.0f, dimensions[0].z-1.0f);

    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
            {
                block.update_position(glm::vec3((minimum.x + k), (minimum.y + i), (minimum.z - j)), glm::vec3((maximum.x + k), (maximum.y + i), (maximum.z - j)));
                std::pair<int, nullptr_t> temp;
                temp = { rand(), nullptr };
                chunk.insert(temp, block);
                if (chunk_position.contains(block)) how_much_fits++;
            }

    std::cout << "Tyle naliczy³o w teorii: " << how_much_fits << "\n";

    std::cout << "\nTyle weszlo w size: " << chunk.size() << "\n";

    Collisions::AABB area1(glm::vec3(17.0f, 1.0f, -17.0f), glm::vec3(18.0f, 2.0f, -18.0f));
    items = chunk.search(area1);

    if (items.empty()) std::cout << "nie\n";
    else { std::cout << "cos jest.\n"; };

    for (it = items.begin(); it != items.end(); ++it)
    {
        std::cout << "\nWartosc 1: " << it->first << "\n";
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