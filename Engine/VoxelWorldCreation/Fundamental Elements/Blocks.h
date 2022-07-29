#pragma once

//Standard libraries

//Custom libraries
#include<Libraries/GLM/glm.hpp>

//Engine libraries
#include<Engine/Dependencies/Dependencies.h>


/*
* A simple data structure that makes use of the Material struct, an block enum 
* and a few simple methods that return information about the blocks
*/


namespace World {


	class BlockInfo {


	protected:

		/*Texture atlas has to be here, so the methods can return complete information about
		any block and make it ready to be drawn to the screen*/

	public:

		/*Initialisation*/
		BlockInfo() {};
		~BlockInfo() {};

		/*Information methods*/
		OpenGL::Material get_block_material(Elements::Blocks block);
		Elements::BlockProperties get_block_properties(Elements::Blocks block);
		uint8_t get_block_toughness(Elements::Blocks block);

	};


	OpenGL::Material get_block_info(Elements::Blocks block)
	{
		switch (block)
		{
		case Elements::Blocks::Stone:
			break;
		case Elements::Blocks::Grass:
			break;
		case Elements::Blocks::Indestructible:
			break;
		}
	}

}