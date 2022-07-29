
// Custom Libraries
#include<glad/glad.h>
#include<glfw3.h>
#include<glfw3native.h>

// Default Libraries
#include<iostream>
#include<typeinfo>
#include<iterator>
#include<chrono>
#include<thread>

// Game Files
#include<Engine/DataStructures/Octree.h>
#include<Engine/DataStructures/ContainedOctree.h>
#include<Engine/DataStructures/QuadTree.h>



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

    Collisions::AABB chunk_position(glm::vec3(0.0f), glm::vec3(16.0f, 16.0f, -16.0f));
    DataStructures::Octree<int> chunk(chunk_position, 3, 1);

    glm::vec3 minimum, maximum;
    minimum = glm::vec3(0.0f);
    maximum = glm::vec3(1.0f, 1.0f, -1.0f);
    Collisions::AABB block(minimum, maximum);

    int how_much_fits = 0;

    srand((unsigned)time(NULL));

    auto t1 = high_resolution_clock::now();

    for (uint8_t i = 0; i < 16; i++)
        for (uint8_t j = 0; j < 16; j++)
            for (uint8_t k = 0; k < 16; k++)
            {
                block.update_position(glm::vec3((minimum.x + k), (minimum.y + i), (minimum.z - j)), glm::vec3((maximum.x + k), (maximum.y + i), (maximum.z - j)));
                chunk.insert(rand(), block);
                /*if (chunk_position.contains(block)) how_much_fits++;*/
            }

    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    std::list<int> items;
    Collisions::AABB area(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(2.0f, 2.0f, -2.0f));
    chunk.dfs(area, items);
    std::list<int>::iterator it;

    if (items.empty()) std::cout << "nie\n";
    else { std::cout << "cos jest.\n"; };

    for (it = items.begin(); it != items.end(); ++it)
    {
        std::cout << "\nWartosc 1: " << *it << "\n";
    }

    std::cout << "Tyle naliczy³o w teorii: " << how_much_fits << "\n";

    std::cout << "\nTyle weszlo w size: " << chunk.size() << "\n";

    std::array<glm::vec3, 2> dimensions = chunk.aabb().bounding_region();

    std::cout << "Dimensions are: " << dimensions[0][0] << ", " << dimensions[0][1] << ", " << dimensions[0][2] << "\n"
        << dimensions[1][0] << ", " << dimensions[1][1] << ", " << dimensions[1][2] << "\n";


    std::pair<std::list<std::pair<int, nullptr_t>>, bool> resize_result;
    chunk.resize({ glm::vec3(16.0f, 0.0f, -16.0f), glm::vec3(32.0f, 16.0f, -32.0f) });

    dimensions = chunk.aabb().bounding_region();

    std::cout << "Dimensions are: " << dimensions[0][0] << ", " << dimensions[0][1] << ", " << dimensions[0][2] << "\n"
        << dimensions[1][0] << ", " << dimensions[1][1] << ", " << dimensions[1][2] << "\n";

    minimum = dimensions[0];
    maximum = glm::vec3(dimensions[0].x + 2.0f, dimensions[0].y + 2.0f, dimensions[0].z - 2.0f);


    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
            {
                block.update_position(glm::vec3((minimum.x + 2.0*k), (minimum.y + 2.0 * i), (minimum.z - 2.0 * j)), glm::vec3((maximum.x + 2.0 * k), (maximum.y + 2.0 * i), (maximum.z - 2.0 * j)));
                chunk.insert(rand(), block);
                //if (chunk_position.contains(block)) how_much_fits++;
            }

    std::cout << "Tyle naliczy³o w teorii: " << how_much_fits << "\n";

    std::cout << "\nTyle weszlo w size: " << chunk.size() << "\n";

    Collisions::AABB area1(glm::vec3(17.0f, 1.0f, -17.0f), glm::vec3(18.0f, 2.0f, -18.0f));
    Collisions::AABB area2(glm::vec3(16.0f, 0.0f, -16.0f), glm::vec3(32.0f, 16.0f, -32.0f));
    items.clear();
    chunk.bfs(area1, items);

    if (items.empty()) std::cout << "nie\n";
    else { std::cout << "cos jest.\n"; };

    for (it = items.begin(); it != items.end(); ++it)
    {
        std::cout << "\nWartosc 1: " << *it << "\n";
    }

    items.clear();
    chunk.dfs(area1, items);

    if (items.empty()) std::cout << "nie\n";
    else { std::cout << "cos jest.\n"; };

    for (it = items.begin(); it != items.end(); ++it)
    {
        std::cout << "\nWartosc 1: " << *it << "\n";
    }

    //

    items.clear();
    chunk.erase_area(area1, items);

    for (it = items.begin(); it != items.end(); ++it)
    {
        std::cout << "\nWartosc 1: " << *it << "\n";
    }

    std::cout << "size to: " << chunk.size();

    std::list<int> shift;
    std::list<Collisions::AABB> free_nodes;

    
       
    //chunk.shift(1, Direction::West, shift, free_nodes);
    
    



    std::cout << "\nIle p[rzetrwalo: " << shift.size() << "\n";

    DataStructures::ContainedOctree<int> jaja({ glm::vec3(16.0f, 0.0f, -16.0f), glm::vec3(32.0f, 16.0f, -32.0f) }, 3, 2);

    dimensions = jaja.aabb().bounding_region();

    std::cout << "Dimensions are: " << dimensions[0][0] << ", " << dimensions[0][1] << ", " << dimensions[0][2] << "\n"
        << dimensions[1][0] << ", " << dimensions[1][1] << ", " << dimensions[1][2] << "\n";

    minimum = dimensions[0];
    maximum = glm::vec3(dimensions[0].x + 2.0f, dimensions[0].y + 2.0f, dimensions[0].z - 2.0f);


    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
            {
                block.update_position(glm::vec3((minimum.x + 2.0 * k), (minimum.y + 2.0 * i), (minimum.z - 2.0 * j)), glm::vec3((maximum.x + 2.0 * k), (maximum.y + 2.0 * i), (maximum.z - 2.0 * j)));
                jaja.insert(rand(), block);
                //if (chunk_position.contains(block)) how_much_fits++;
            }


    std::list<std::pair<int, Collisions::AABB>> returning;

    t1 = high_resolution_clock::now();

    std::cout << "SIZE CONT: " << jaja.size() << "\n";

    jaja.shift(3, Coordinates::Directions::North, returning);

    t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    typename std::list<std::pair<int, Collisions::AABB>>::iterator iter;

    std::cout << "SIZE CONT: " << jaja.size() << "\n";

    //The chunk testing now

    returning.clear();


    t1 = high_resolution_clock::now();

    //std::cout << "SIZE CONT: " << chunk.size() << "\n";

    chunk.shift(3, Coordinates::Directions::North, returning);

    t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    Collisions::AABB chunk_border(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(16.0f, 16.0f, -16.0f));
    chunk_border.update_position(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(16.0f, 16.0f, -16.0f));
    DataStructures::ContainedOctree<int> chunk1(chunk_border, 5, 1);

    dimensions = chunk1.aabb().bounding_region();

    std::cout << "Dimensions are: " << dimensions[0][0] << ", " << dimensions[0][1] << ", " << dimensions[0][2] << "\n"
        << dimensions[1][0] << ", " << dimensions[1][1] << ", " << dimensions[1][2] << "\n";

    minimum = dimensions[0];
    maximum = glm::vec3(dimensions[0].x + 1.0f, dimensions[0].y + 1.0f, dimensions[0].z - 1.0f);

    std::vector<int> chunk2;
    //chunk2.reserve(32 * 32 * 32);
    std::array<int, 32*32*32> chunk3;

    // t1 = high_resolution_clock::now();

    //for (int i = 0; i < 32; i++)
    //    for (int j = 0; j < 32; j++)
    //        for (int k = 0; k < 32; k++)
    //        {
    //            block.update_position(glm::vec3((minimum.x + k), (minimum.y + i), (minimum.z - j)), glm::vec3((maximum.x + k), (maximum.y + i), (maximum.z - j)));
    //            chunk1.insert(rand(), block);
    //            //if (chunk_position.contains(block)) how_much_fits++;
    //            //chunk2.push_back(rand());
    //        }

    //std::list<typename std::list<DataStructures::OctreeItem<int>>::iterator> data;
    Collisions::AABB search(glm::vec3(15.0f, 13.0f, -11.0f), glm::vec3(16.0f, 14.0f, -12.0f));

   

    //chunk1.dfs(search, data);

    //for (const auto& it : data)
    //{
    //    std::cout << it->item << "\n";
    //}

    //chunk_border.intersects2(chunk1.aabb());

    t1 = high_resolution_clock::now();

    for (int i = 0; i < 32768; i++)
    {
        chunk3[i] = rand();
    } 

        t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";


    
    

    for(int i = 0; i < 32; i++)
        for(int j = 0; j < 32; j++)
            for (int k = 0; k < 32; k++)
            {
                Collisions::AABB temp(glm::vec3((minimum.x + k), (minimum.y + i), (minimum.z - j)), glm::vec3((maximum.x + k), (maximum.y + i), (maximum.z - j)));
                if (temp.contains(search))
                {
                    std::cout << "\n" << chunk3[256 * i + 16 * j + k] << "\n";
                    break;
                }
                    
            }





    //shift.clear();
    //free_nodes.clear();

    //t1 = high_resolution_clock::now();

    //chunk.shift(1, Direction::North, shift, free_nodes);

    //t2 = high_resolution_clock::now();

    ///* Getting number of milliseconds as an integer. */
    //ms_int = duration_cast<milliseconds>(t2 - t1);

    ///* Getting number of milliseconds as a double. */
    //ms_double = t2 - t1;

    //std::cout << ms_int.count() << "ms\n";
    //std::cout << ms_double.count() << "ms\n";

//chunk.bfs(area2, items);
//    
//
//    /* Getting number of milliseconds as an integer. */
//    ms_int = duration_cast<milliseconds>(t2 - t1);
//
//    /* Getting number of milliseconds as a double. */
//    ms_double = t2 - t1;
//
//    std::cout << ms_int.count() << "ms\n";
//    std::cout << ms_double.count() << "ms\n";

    

    //for (iter = shift.begin(); iter != shift.end(); ++iter)
    //{
    //    std::cout << "\nWartosc 1: " << (*iter).first << "\n";
    //}



    DataStructures::QuadTree<int> quad({ glm::vec3(-256.0f, 0.0f, 256.0f), glm::vec3(256.0f, 256.0f, -256.0f) }, 1, 32);


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