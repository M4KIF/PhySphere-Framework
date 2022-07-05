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

class AABB
{
	// Place for the aliasing and needed private functions or Lambdas

	using BoxCoordinates = std::array<glm::vec3, 2>;

protected:

	// Contains the center of the box as of seen from the top

	glm::vec3 m_Center;

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

public:

	// Initialisation

	AABB();

	// Sets up a valid bounding box for further use

	AABB(glm::vec3 UpperTopLeft, glm::vec3 LowerBottomRight);

	// Copyies the Box

	AABB(AABB& Copy);

	// Disposes the bounding box

	~AABB();

	// Access

	glm::vec3 Center(void);
	BoxCoordinates BoundingRegion();
	glm::vec3 Dimensions();

	// Comparsion 

	bool Collides(AABB& compared);
	bool Contains(AABB& compared);

	// Updating 

	void Update(glm::vec3 Minimum, glm::vec3 Maximum);
};

