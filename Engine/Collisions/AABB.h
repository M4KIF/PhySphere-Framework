#pragma once

// Custom Libraries
#include<glm/glm.hpp>

// Default Libraries
#include<array>
#include<vector>

//
// This object is set to contain all of the needed information to properly
// describe an AABB type of Bounding Box
//



/////////////////////////////////////////////
// How does the Min and Max work in an AABB /
//	  0 ----- MAX							/
//	 /'       /'							/
//	2 ------ 3 '							/
//	' '      ' '							/
//	' 4      ' 5							/
//	'/       '/								/
//	MIN ---- 7								/
/////////////////////////////////////////////



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

		// These variable contain the MIN/MAX values of the box
		BoxCoordinates m_MinMax{};

		// Flags
		bool m_CenterUpdated = false;
		bool m_DimensionsUpdated = false;

	public:

		/*//////////////////
		* / Initialisation /
		*///////////////////

		AABB();
		AABB(glm::vec3 Minimum, glm::vec3 Maximum);
		AABB(const AABB& Copy);
		~AABB();

		/*//////////////////
		* / Element access /
		*///////////////////

		glm::vec3 center(void);
		BoxCoordinates bounding_region();
		glm::vec3 dimensions();

		/*////////////////////
		* / Basic Collisions /
		*/////////////////////

		bool contains(AABB& object); //Contains the whole object
		bool contains_a_point(glm::vec3 object);
		bool intersects1(AABB& object); //Either contains or colides partly(side to side) or totally
		bool intersects2(AABB& object);
		bool intersects_strictly(AABB& object); //Either contains or colides totally

		/*//////////////////////
		* / Precise Collisions /
		*///////////////////////

		bool left_collision(AABB& object);
		bool right_collision(AABB& object);
		bool front_collision(AABB& object);
		bool back_collision(AABB& object);
		bool top_collision(AABB& object);
		bool bottom_collision(AABB& object);

		/*/////////////
		* / Modifiers /
		*//////////////

		void update_position(glm::vec3 Minimum, glm::vec3 Maximum);
	};

}
