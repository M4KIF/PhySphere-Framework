#pragma once

//Standard libraries

//Custom libraries

//Engine libraries
#include<Engine/Dependencies/Dependencies.h>
#include<Engine/Collisions/AABB.h>

//Constants
#define CHUNK_SIZE 32
#define CHUNK_VOLUME CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE


/*
* This class stores the smallest amount possible of informations
* needed to enable the chunk functionality in the engine. The array of 
* blocks consists only of int, that are later translated to blocks in the end
* of the rendering pipeline.
*/

namespace World {

	class Chunk {

		using Position = Collisions::AABB;

	protected:

		//Stores the Bounding Box of the chunk
		Position m_Position;

		//Stores the block data
		std::array<Elements::Blocks, CHUNK_VOLUME> m_Blocks;

		//Emptyness flag, activated only after the for-loop thats sets all blocks to air
		bool m_Empty = false;

	public:

		/*
		* Initialisation
		*/

		Chunk();
		Chunk(Collisions::AABB bounding_box);
		~Chunk();

		/*
		* Capacity
		*/

		size_t size();
		size_t max_size();
		bool empty();
		void clear();

		/*
		* Position
		*/

		void update_aabb(Collisions::AABB bounding_box);
		Collisions::AABB get_aabb();
		bool find_collision(Collisions::AABB object); //Checks whether something collides
		std::vector<Coordinates::Directions> which_side_collides(Collisions::AABB object); //Checks from which sides something collides with the chunks blocks

		/*
		* Data
		*/

		std::array<Elements::Blocks, CHUNK_VOLUME>* get_block_data();
		void set_block_data(std::array<Elements::Blocks, CHUNK_VOLUME> data);

	};

}