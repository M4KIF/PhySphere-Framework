#pragma once

// Custom Libraries
#include<glm.hpp>

// Default Libraries
#include<array>
#include<vector>

//
// This object is set to contain all of the needed information to properly
// describe an AABB type of Bounding Box
//

namespace Collisions {

	class AABB
	{
		// Place for the aliasing and needed private functions or Lambdas

		using BoxCoordinates = std::array<glm::vec3, 2>;

	protected:

		// Contains the center of the box as of seen from the top
		glm::vec3 m_Center;

		//Contains all side lengths
		glm::vec3 m_Dimensions;

		// How does the Min and Max work in an AABB
		//	  0 ----- MAX
		//	 /'       /'
		//	2 ------ 3 '
		//	' '      ' '
		//	' 4      ' 5
		//	'/       '/
		//	MIN ---- 7

		// These variable contain the MIN/MAX values of the box
		BoxCoordinates m_MinMax{};

		// Flags
		bool m_CenterUpdated = false;
		bool m_DimensionsUpdated = false;

	public:

		/*
		* Initialisation
		*/

		AABB();

		// Sets up a valid bounding box for further use
		AABB(glm::vec3 Minimum, glm::vec3 Maximum);

		// Copyies the Box
		AABB(AABB& Copy);

		// Disposes the bounding box
		~AABB();

		/*
		* Element access
		*/

		glm::vec3 center(void);
		BoxCoordinates bounding_region();
		glm::vec3 dimensions();

		/*
		* Element access
		*/

		bool contains(AABB& compared); //Contains the whole object
		bool contains(glm::vec3 compared);
		bool intersect1(AABB& comapred); //Contains either a part, or the whole object
		bool intersect2(AABB& comapred);

		// Updating 

		void update_position(glm::vec3 Minimum, glm::vec3 Maximum);
	};

}
