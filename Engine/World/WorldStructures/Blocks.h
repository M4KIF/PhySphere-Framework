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

namespace OpenGL {

	struct Material {

		// Variables needed for the material functionality
		glm::vec3 m_Ambient = glm::vec3(0.0f);
		glm::vec3 m_Diffuse = glm::vec3(0.0f);
		glm::vec3 m_Specular = glm::vec3(0.0f);
		float m_Shininess = 0.0f;

		// Overloaded "=" operator for quick value pushing
		Material& operator=(const Material& material) {

			//Copying the data
			this->m_Ambient = material.m_Ambient;
			this->m_Diffuse = material.m_Diffuse;
			this->m_Specular = material.m_Specular;
			this->m_Shininess = material.m_Shininess;

			//Returning the finished object
			return *this;
		}

	};

}

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