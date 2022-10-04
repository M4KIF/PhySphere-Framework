//#pragma once
//
////Standard libraries
//
////Custom libraries
//
////Engine libraries
//#include<Engine/Dependencies/Dependencies.h>
//#include<Engine/DataStructures/ContainedOctree.h>
//#include<Engine/DataStructures/ContainedQuadTree.h>
//#include<Engine/VoxelWorldCreation/Fundamental Elements/Chunk.h>
//
////Constants
//
//
///*
//* This class will focus on collecting all of the chunk and enabling the
//* creation of the chunk grid that will be later processed by the rendering pipeline.
//* I think of It as so, It will consist of one 
//* Quadtree container(1st Level, but overall it depends on the setting, more levels here = more render distance)
//* and 4 (3rd Level)Octree containers, assuming that the chunk size = 32.
//*/
//
//
//namespace World {
//
//	//The syntax resembles the Octree and Quadtree container syntax combined
//	class ChunkTree
//	{
//
//		using Position = Collisions::AABB;
//
//		/*
//		* Private member functions
//		*/
//
//		//Preprares the coordinates for Octrees from the Map position
//		void calculate_octrees_bounds();
//
//	protected:
//		
//		//The area that the map is storing
//		Position m_Area;
//		
//		//How much Octress will be processed
//		size_t m_Octrees_Number;
//		
//		//Storing the children data
//		std::vector<DataStructures::ContainedOctree<Chunk>*> m_Octrees;
//
//		//Maximum depth of the map QuadTree
//		Settings::RenderDistance m_Map_Depth;
//
//		//The main part of the chunk grid, the 2D data storage
//		DataStructures::ContainedQuadTree<DataStructures::ContainedOctree<Chunk>*> m_Map;
//
//		//Flags
//
//		bool m_OctreesReady;
//		bool m_Shifting;
//
//
//	public:
//
//		/*
//		* Initialisation
//		*/
//
//		ChunkTree();
//		ChunkTree(Collisions::AABB area);
//		ChunkTree(Settings::RenderDistance value, Collisions::AABB area);
//		ChunkTree(const ChunkTree& copy);
//		~ChunkTree();
//
//		/*
//		* Dimensions && Position
//		*/
//
//		Collisions::AABB aabb();
//		std::vector<Collisions::AABB> octrees_aabb();
//		size_t current_render_distance();
//
//		/*
//		* Capacity
//		*/
//
//		size_t size();
//		bool empty();
//
//		/*
//		* Element access
//		*/
//
//		std::vector<DataStructures::ContainedOctree<Chunk>*> access_octrees();
//		std::vector<DataStructures::ContainedOctree<Chunk>*> dfs(Collisions::AABB area);
//		std::vector<DataStructures::ContainedOctree<Chunk>*> bfs(Collisions::AABB area);
//		bool contains(Collisions::AABB area);
//
//		/*
//		* Modifiers
//		*/
//
//		bool resize(Settings::RenderDistance new_render_distance);
//		bool clear();
//
//		/*
//		* Movement
//		*/
//
//		void shift(size_t nodes_to_shift, Coordinates::Directions shifting_direction, std::list<std::pair<Chunk, Collisions::AABB>>& returned_data);
//
//	};
//
//
//}
//
