#pragma once

#include<Libraries/GLM/glm.hpp>

/*
* Here are the declaration of all of the needed structs
* for the Trees to work.
*/


namespace Trees {

	template<typename T>
	struct Location
	{
		typename std::list<T>* items_container = nullptr;
		typename std::list<T>::iterator items_iterator;
		typename Collisions::AABB aabb;
	};

}

	
namespace Coordinates {

	enum class Directions : unsigned char {
		North = 0x01, // = 0b00000001 -> 1 << 1
		South = 0x02, // = 0b00000010 -> 1 << 2,
		East = 0x04, // = 0b00000100 -> 1 << 3,
		West = 0x08 // = 0b00001000 -> 1 << 4
	};

}


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

namespace Elements {

	enum class Blocks : unsigned short int {
		Indestructible = 1,
		Grass,
		Stone,
		OakWood,
		Water,
		Lava,
	};

	struct BlockProperties {
		bool m_Destroyable;
		bool m_Liquid;
	};

}