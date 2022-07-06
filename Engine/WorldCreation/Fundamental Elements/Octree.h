#pragma once

// Custom Libraries

// Default Libraries
#include<list>
#include<memory>
#include<iostream>

// Game files
#include<Engine/WorldCreation/Fundamental Elements/AABB.h>

//Macros

#define MINIMUM_BOUNDING_SIZE 1.0f
#define NUMBER_OF_OCTANTS 8

//
// This Octree implementation is intended to be used both as 
// the main blocks container and also as a main chunk container,
// both with different maximum levels variable. Also before that, It
// will be wrapped to use in conjunction with a list container that will
// store the content of the Tree itself
//



template<typename T, size_t MaxDepth>
class Octree
{
	// Place for the Aliases

	using OctantBoxes = std::array<AABB, 8>;

	// Trick for storing the data about Octants

	enum class Octants : unsigned char {
		// The values below translate to hex values as follows

		O1 = 0x01, // = 0b00000001 -> 1 << 1
		O2 = 0x02, // = 0b00000010 -> 1 << 2
		O3 = 0x04, // = 0b00000100 -> 1 << 3
		O4 = 0x08, // = 0b00001000 -> 1 << 4
		O5 = 0x10, // = 0b00010000 -> 1 << 5
		O6 = 0x20, // = 0b00100000 -> 1 << 6
		O7 = 0x40, // = 0b01000000 -> 1 << 7
		O8 = 0x80  // = 0b10000000 -> 1 << 8

		// When all children are active this should be equal to 0b11111111
	};

	// Private member methods

	void CalculateOctantBounds(AABB& BoundingBox, Octants Octant);
	
	// Return true only if the Octants array has nullptrs in it

	bool IsLeafNode(void);

	// Recursively comes down till the depth reaches maximum

	bool Subdivide(void);


protected:

	// The area that the Octree contains

	AABB m_Position;

	// Depth checking

	size_t m_MaxDepth = MaxDepth;
	size_t m_Depth = 0;

	// A clever way of knowing whether the Octants are active
	// if the value is shifted 8 times to the left, that means, that all of the octants have been set

	unsigned char m_ActiveOctants; 
	
	// The bounds of the potential Octants

	OctantBoxes m_OctantsBounds;

	// The Octants themselves, will be made with the use of a bounds calulating function

	std::array<std::shared_ptr<Octree<T, (size_t)(MaxDepth)>>, 8> m_Octants;

	// The flag set

	bool m_IsLeafNode = false;

	bool m_TreeReady = false;

	bool m_TreeBuilt = false;

	// A pointer to the element that the node will be storing

	std::list<std::shared_ptr<T>> m_Item;

	// A queue for filling the data to the tree

	std::list<std::shared_ptr<T>> m_Queue;

public:

	// Initialisation

	// Sets up the environment

	Octree();

	// Initialises the tree and gives it the knowledge about it's position

	Octree(AABB BoundingBox);

	// For creating the internal nodes

	Octree(AABB BoundingBox, size_t Depth);

	// Sets up the tree completely with the data

	Octree(AABB BoundingBox, size_t Depth, std::list<std::shared_ptr<T>> Items);

	// Disposes the tree Recursively and displaces all the items that the tree references to

	~Octree();

	// Access methods

	bool Search();

	// Capacity

	void Empty();
	void Size();
	size_t MaximumDepth();
	size_t CurrentDepth();

	// Modifying methods

	void Build();
	void Insert();
	void Resize();
	void Clear();

	// Updating methods

	void Update();
	void ProccessPending();

	// Desiplacing and cleaning methods

	void Destroy();

};

//
// Definitions
// 

// Constructors

template<typename T, size_t MaxDepth>
Octree<T, MaxDepth>::Octree()
{
	//Default constructor
}

template<typename T, size_t MaxDepth>
Octree<T, MaxDepth>::Octree(AABB BoundingBox) :
	m_Position(BoundingBox)
{
	// Sets the leaf flag accordingly

	m_IsLeafNode = true;

	// Proceeds to subdivision

	Subdivide();
}

template<typename T, size_t MaxDepth>
Octree<T, MaxDepth>::Octree(AABB BoundingBox, size_t Depth) :
	m_Position(BoundingBox), m_Depth(Depth)
{
	// Sets the leaf flag accordingly

	m_IsLeafNode = true;
	
	// Sets the current level

	m_Depth = Depth;

	// Proceeds to subdivision

	Subdivide();
}

template<typename T, size_t MaxDepth>
Octree<T, MaxDepth>::~Octree()
{
	// Default
}

// Access Methods

template<typename T, size_t MaxDepth>
bool Octree<T, MaxDepth>::Search()
{

}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Empty()
{

}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Size()
{

}

template<typename T, size_t MaxDepth> inline
size_t Octree<T, MaxDepth>::MaximumDepth()
{
	return m_MaxDepth;
}

template<typename T, size_t MaxDepth> inline
size_t Octree<T, MaxDepth>::CurrentDepth()
{
	return m_Depth;
}

// Modifying methods

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Build()
{

}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Insert()
{

}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Resize()
{

}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Clear()
{

}

// Updating methods

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Update()
{

}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::ProccessPending()
{

}

// Cleaning up

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Destroy()
{

}

//
// Private member functions
//

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::CalculateOctantBounds(AABB& BoundingBox, Octants Octant)
{
	glm::vec3 Center = m_Position.Center();

	// Calculating the 8 different boudning boxes for the Octants

	if (Octant == Octants::O1)
	{

		return;
	}
	else if (Octant == Octants::O2)
	{

		return;
	}
	else if (Octant == Octants::O2)
	{

		return;
	}
	else if (Octant == Octants::O3)
	{

		return;
	}
	else if (Octant == Octants::O4)
	{

		return;
	}
	else if (Octant == Octants::O5)
	{

		return;
	}
	else if (Octant == Octants::O6)
	{

		return;
	}
	else if (Octant == Octants::O7)
	{

		return;
	}
	else if (Octant == Octants::O8)
	{

		return;
	}
}

template<typename T, size_t MaxDepth>
bool Octree<T, MaxDepth>::IsLeafNode(void)
{
	// If the first element is equal to null,
	// then the rest cannot exist either

	return m_IsLeafNode;
}

template<typename T, size_t MaxDepth>
bool Octree<T, MaxDepth>::Subdivide(void)
{
	// It starts with checking if this tree can be subdivided

	if (!IsLeafNode())
	{
		return false;
	}
	else if (m_Depth+1 == m_MaxDepth)
	{
		return false;
	}

	// Calculating the needed dimensions

	glm::vec3 Dimensions = m_Position.Dimensions();

	// TODO: This safetycheck doesnt work at all

	//for (int i = 0; i < 3; i++)
	//{
	//	std::cout << "Hey!\n";
	//	if (Dimensions[i] < MINIMUM_BOUNDING_SIZE) return false;
	//}

	// Creating the coordinates of the Octants, I am using a clever little technique,
	// by shifting bit-wise a number one, I achieve the needed enum class members values,
	// that allows to correctly recognize Octants based on their hex code.

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		CalculateOctantBounds(m_OctantsBounds[i], static_cast<Octants>(1<<i));
		std::cout << "Hey!\n";
	}

	// Creating the Octants themselves

	m_IsLeafNode = false;

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		m_Octants[i] = std::make_shared<Octree<T, MaxDepth>>(m_OctantsBounds[i], m_Depth+1);
		std::cout << m_Octants[i] << ": Adres!\n";
	}
}

