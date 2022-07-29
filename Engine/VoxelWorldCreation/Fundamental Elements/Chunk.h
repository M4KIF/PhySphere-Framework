#pragma once

//Standard libraries

//Custom libraries
#include<Libraries/GLM/glm.hpp>

//Engine libraries
#include<Engine/Dependencies/Dependencies.h>
#include<Engine/Collisions/AABB.h>

//Constants
#define CHUNK_SIZE 32


/*
* 
*/


class Chunk {

	using Position = Collisions::AABB;

protected:

	//Stores the Bounding Box of the chunk
	Position m_Position;

	//Stores the block data
	std::array<Elements::Blocks, CHUNK_SIZE* CHUNK_SIZE* CHUNK_SIZE> m_Blocks;

	//

public:

	Chunk() {};
	~Chunk() {};

	void update_position();
	Collisions::AABB aabb();
	Collisions::AABB find_collision(); //Searches for all aabb's taht collide with the given aabb, then I 
	//Can check them and make me slide, fall, or get up to speed

};