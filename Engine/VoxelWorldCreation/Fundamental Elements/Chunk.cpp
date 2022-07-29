#include "Chunk.h"



namespace World {

	//Only sets the emptyness flag, as an array is clear from default
	Chunk::Chunk()
	{

		m_Empty = true;

	}


	//Presets the position of the chunk and sets the emptyness flag, as an array is clear from default
	Chunk::Chunk(Collisions::AABB bounding_box)
		: m_Position(bounding_box)
	{

		m_Empty = true;

	}


	Chunk::~Chunk()
	{

		//Also does nothing currently

	}


	//Returns the current size, without counting "empty" elements
	size_t Chunk::size()
	{
		size_t size;

		for (uint16_t i = 0; i < m_Blocks.max_size(); i++)
			if (m_Blocks[i] != Elements::Blocks::Air) size++;

		return size;
	}


	//Returns the blocks array size
	size_t Chunk::max_size()
	{
		return m_Blocks.max_size();
	}


	//Returns the emptyness flag
	bool Chunk::empty()
	{
		for (uint16_t i = 0; i < m_Blocks.max_size(); i++)
		{
			if (m_Blocks[i] != Elements::Blocks::Air)
			{
				m_Empty = false;
				return m_Empty;
			}
			else
			{
				continue;
			}

		}

		//If it manages to come down here, then it has to be empty
		m_Empty = true;

		//Returning the flag
		return m_Empty;
	}


	//Clears the chunk
	void Chunk::clear()
	{

		//Sets the chunk blocks to air
		for (uint16_t i = 0; i < m_Blocks.size(); i++)
		{
			m_Blocks[i] = Elements::Blocks::Air;
		}

		//Activating the emptyness flag
		m_Empty = true;

	}


	//Updates the position
	void Chunk::update_aabb(Collisions::AABB bounding_box)
	{

		//Updating the bounding box
		m_Position = bounding_box;

		//If the position gets updated, then the currently stored data gets invalidated 
		clear();

	}


	//Returns the position
	Collisions::AABB Chunk::get_aabb()
	{
		return m_Position;
	}


	//Returns a boolean that states whether our object collides with the chunk or not
	bool Chunk::find_collision(Collisions::AABB object)
	{
		return object.intersects2(m_Position);
	}


	//Checks from which side the collisions happened
	std::vector<Coordinates::Directions> Chunk::which_side_collides(Collisions::AABB object)
	{

		//TODO: a little bit bigger topic.

		/*
		* I have to find the exact localisation of the given object and then check all-round for sollisions;
		*/

		return std::vector<Coordinates::Directions>();
	}


	//Gives back the pointer to the blocks array
	std::array<Elements::Blocks, CHUNK_VOLUME>* Chunk::get_block_data()
	{
		return &m_Blocks;
	}


	//Sets the block data with a new array
	void Chunk::set_block_data(std::array<Elements::Blocks, CHUNK_VOLUME> data)
	{
		m_Blocks.swap(data);
	}

}
