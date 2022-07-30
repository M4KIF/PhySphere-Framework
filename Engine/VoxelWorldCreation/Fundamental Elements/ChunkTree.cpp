//Custom Libraries
#include<Libraries/THREADPOOL/BS_thread_pool.hpp>

//Default Libraries

//Game files
#include "ChunkTree.h"



//The code is multithreaded.
namespace World{


    //Sets the default map size to the lowest setting possible
    ChunkTree::ChunkTree():
        m_Map_Depth(Settings::RenderDistance::Low),
        m_Octrees_Number(std::pow(std::pow(2, (int)Settings::RenderDistance::Low), 2))
    {

    }


    //Sets the default map size to the lowest setting possible and prepares the area
    ChunkTree::ChunkTree(Collisions::AABB area):
        m_Map_Depth(Settings::RenderDistance Low),
        m_Octrees_Number(std::pow(std::pow(2, (int)Settings::RenderDistance::Low), 2)),
        m_Area(area)
    {
        calculate_octrees_bounds();
    }


    //Sets the Map depth accordint to the user preference
    ChunkTree::ChunkTree(Settings::RenderDistance value, Collisions::AABB area):
        m_Map_Depth(value),
        m_Octrees_Number(std::pow(std::pow(2, (int)m_Map_Depth), 2)),
        m_Area(area)
    {
        //
    }


    //Copying constructor
    ChunkTree::ChunkTree(const ChunkTree& copy)
    {
        this->m_Area = copy.m_Area;
        this->m_Map = copy.m_Map;
        this->m_Map_Depth = copy.m_Map_Depth;
        this->m_Octrees = copy.m_Octrees;
        this->m_Octrees_Number = copy.m_Octrees_Number;
        this->m_OctreesReady = copy.m_OctreesReady;
        this->m_Shifting = copy.m_Shifting;
    }


    //Destroys the octrees stored in the vector of pointers
    ChunkTree::~ChunkTree()
    {
        //TODO: Clear the pointers out of the Octrees safely
    }


    //The current bounding box of the chunk_map
    Collisions::AABB ChunkTree::aabb()
    {

    }


    //The bounding boxes of the stored octrees
	std::vector<Collisions::AABB> ChunkTree::octrees_aabb()
    {

    }


    //Current render distance = chunk_quadtree_depth
	size_t ChunkTree::current_render_distance()
    {

    }


    //Size in the number of Octrees contained
    size_t ChunkTree::size()
    {

    }


    //Is the whole structure empty?
	bool ChunkTree::empty()
    {

    }


    //Gives back pointers to all stored Octrees, mainly for the other functions to use them
	std::vector<DataStructures::ContainedOctree<Chunk>*> ChunkTree::access_octrees()
    {

    }


    //Searches for the chunk that stores the given area with DFS algorithm
	std::vector<DataStructures::ContainedOctree<Chunk>*> ChunkTree::dfs(Collisions::AABB area)
    {

    }


    //Searches for the chunk that stores the given area with BFS algorithm
	std::vector<DataStructures::ContainedOctree<Chunk>*> ChunkTree::bfs(Collisions::AABB area)
    {

    }


    //Returns a boolean flag with containing statement
	bool ChunkTree::contains(Collisions::AABB area)
    {

    }


    //Doesn't change the exact position, only expands the current structure and prepares to fill with data
	bool ChunkTree::resize(CSettings::RenderDistance new_render_distance)
    {

    }


    //Clears all of the trees and the quadtree
	bool ChunkTree::clear()
    {

    }


    //Moves the structure in space
    void ChunkTree::shift(size_t nodes_to_shift, 
    Coordinates::Directions shifting_direction, 
    std::list<std::pair<Chunk, Collisions::AABB>>& returned_data)
    {

    }


}

