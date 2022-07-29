#pragma once

//Standard libraries

//Custom libraries

//Engine libraries
#include<Engine/Dependencies/Dependencies.h>
#include<Engine/DataStructures/ContainedOctree.h>
#include<Engine/DataStructures/ContainedQuadTree.h>
#include<Engine/VoxelWorldCreation/Fundamental Elements/Chunk.h>

//Constants


/*
* This class will focus on collecting all of the chunk and enabling the
* creation of the chunk grid that will be later processed by the rendering pipeline.
* I think of It as so, It will consist of one 
* Quadtree container(1st Level, but overall it depends on the setting, more levels here = more render distance)
* and 4 (3rd Level)Octree containers, assuming that the chunk size = 32.
*/


namespace World {


	class ChunkTree
	{

		using Position = Collisions::AABB;

	protected:
		
		//The area that the map is storing
		Position m_Area;
		
		//How much Octress will be processed
		size_t m_Children_number;
		
		//Storing the children data
		std::vector<DataStructures::ContainedOctree<Chunk>*> m_Children;

		//The main part of the chunk grid, the 2D data storage
		DataStructures::ContainedQuadTree<DataStructures::ContainedOctree<Chunk>*> m_Map;

		//Flags

	public:

		ChunkTree();
		ChunkTree()



	};


}

