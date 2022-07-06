#pragma once

//Custom Libraries

//Default Libraries
#include<list>
#include<memory>
#include<iostream>

//Game files
#include<Engine/WorldCreation/Fundamental Elements/AABB.h>

//Macros

#define MINIMUM_DIMENSION 1.0f
#define NUMBER_OF_OCTANTS 8


/*
* This Octree implementation is intended to be used both as 
* the main blocks container and also as a main chunk container,
* both with different maximum levels variable. Also before that, It
* will be wrapped to use in conjunction with a list container that will
* store the content of the Tree itself.
* 
* Made with the help of:
* javidx9: https://www.youtube.com/watch?v=ASAowY6yJII&t=1156s
* World of Zero: https://www.youtube.com/watch?v=m0guE7804to
* 
*/

template<typename T, size_t MaxDepth>
class Octree
{
	//Place for the Aliases

	using OctantBoxes = std::array<AABB, 8>;

	//Trick for storing the data about Octants

	enum class Octants : unsigned char {
		//The values below translate to hex values as follows

		O1 = 0x01, // = 0b00000001 -> 1 << 1
		O2 = 0x02, // = 0b00000010 -> 1 << 2
		O3 = 0x04, // = 0b00000100 -> 1 << 3
		O4 = 0x08, // = 0b00001000 -> 1 << 4
		O5 = 0x10, // = 0b00010000 -> 1 << 5
		O6 = 0x20, // = 0b00100000 -> 1 << 6
		O7 = 0x40, // = 0b01000000 -> 1 << 7
		O8 = 0x80  // = 0b10000000 -> 1 << 8

		//When all children are active this should be equal to 0b11111111
	};

	//Private member methods

	void CalculateOctantBounds(AABB& BoundingBox, Octants Octant);
	
	//Return true only if the Octants array has nullptrs in it

	bool IsLeafNode(void);

	//Recursively comes down till the depth reaches maximum

	bool Subdivide(void);

	//Recursive search function
	void search(const AABB& area, std::list<typename T>& items);

	//Pushes all of the items from the node
	void Items(std::list<typename T>& items);


protected:

	// The area that the Octree contains

	AABB m_Position;

	// Depth checking

	const size_t m_MaxDepth = MaxDepth;
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

	std::list<std::shared_ptr<T>> m_Items;

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

	std::list<T> Search(const AABB& area);
	bool Contains(const AABB& area);

	// Capacity

	void Empty();
	size_t Size();
	size_t MaximumDepth();
	size_t CurrentDepth();

	// Modifying methods

	bool Build();
	void Insert(T object, AABB area);
	void Resize(glm::vec3 minimum, glm::vec3 maximum);
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
	// Does nothing, because the Octree doesn't have the bounding space defined
}

template<typename T, size_t MaxDepth>
Octree<T, MaxDepth>::Octree(AABB BoundingBox) :
	m_Position(BoundingBox)
{
	// Every octree starts as a leaf node before any subdivisions

	m_IsLeafNode = true;

	// Proceeds to subdivision

	Subdivide();
}

template<typename T, size_t MaxDepth>
Octree<T, MaxDepth>::Octree(AABB BoundingBox, size_t Depth) :
	m_Position(BoundingBox), m_Depth(Depth)
{
	// Every octree starts as a leaf node before any subdivisions

	m_IsLeafNode = true;
	
	// Sets the current level

	m_Depth = Depth;

	// Proceeds to subdivision

	Subdivide();
}

template<typename T, size_t MaxDepth>
Octree<T, MaxDepth>::~Octree()
{
	//Default
}

//Access Methods

template<typename T, size_t MaxDepth>
std::list<T> Octree<T, MaxDepth>::Search(const AABB &area)
{
	/*
	* Returns a list of items that can be found in the
	* specified area of the tree. This number can be in fact quite large
	*/

	std::list<T> items;
	
	//This can go deep into the recursion
	search(area, items);

	return items;

}

template<typename T, size_t MaxDepth>
bool Octree<T, MaxDepth>::Contains(const AABB& area)
{
	return m_Position.Contains(area);
}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Empty()
{

}

template<typename T, size_t MaxDepth>
size_t Octree<T, MaxDepth>::Size()
{

	size_t count = m_Items.size();

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		if (m_Octants[i])
		{
			count += m_Octants[i]->size();
		}
	}

	return count;
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
bool Octree<T, MaxDepth>::Build()
{

}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Insert(T object, AABB area)
{
	// Checking whether anything can be inserted
	if (!m_TreeBuilt)
	{
		return;
	}

	// Checking whether the children can contain the item
	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		if (m_Octants[i]->Contains(area))
		{
			// Within the depth limit?
			if (m_Depth + 1 < m_MaxDepth)
			{
				//If no, does the child exist?
				if (!m_Octants[i])
				{
					//If no, create that child
					m_Octants[i] = std::make_shared<Octree<T, MaxDepth>>(m_OctantsBounds[i], m_Depth + 1);

				}

				//If yes, proceed to the insertion
				m_Octants[i]->Insert(object, area);

				return;
			}
		}	

	}

	//It must be somewhere in the tree, so
	m_Items.push_back(std::make_shared<object>);
}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Resize(glm::vec3 minimum, glm::vec3 maximum)
{
	// Resizing invalids the whole tree

	Clear();

	// Actual resizing of the structure

	m_Position.Update(minimum, maximum);

	// Calcaulating the potential children coordinates

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		CalculateOctantBounds(m_OctantsBounds[i], static_cast<Octants>(1 << i));
	}
}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Clear()
{
	// Clearing the containers that the current node stores

	m_Items.clear();

	// Proceeding to the Octants

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{

		if (m_Octants[i])
		{
			// Recursively cleaning

			m_Octants[i]->clear();

			// Resetting the shared_ptr -> deleting the child

			m_Octants[i]->reset();
		}
		
	}
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
	// Here is the center of the parent node Octree

	glm::vec3 center = m_Position.Center();

	// And It's side length for all dimensions

	glm::vec3 dimensions = m_Position.Dimensions();

	// Variables for storing the min and max valus

	glm::vec3 minimum;
	glm::vec3 maximum;

	// Calculating the 8 different boudning boxes for the Octants

	if (Octant == Octants::O1)
	{
		// The minimum coordinate of the bounding box

		minimum = center;

		// The maximum coordinate of the bounding box

		maximum = glm::vec3((center[0] - 0.5 * dimensions[0]), (center[1] + 0.5 * dimensions[1]), (center[2] - 0.5 * dimensions[2]));

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
	else if (Octant == Octants::O2)
	{	
		// The minimum coordinate of the bounding box

		minimum = glm::vec3((center[0] + 0.5 * dimensions[0]), center[1], center[2]);

		// The maximum coordinate of the bounding box

		maximum = glm::vec3(center[0], (center[1] + 0.5 * dimensions[1]), (center[2] - 0.5 * dimensions[2]));

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
	else if (Octant == Octants::O3)
	{
		// The minimum coordinate of the bounding box

		minimum = glm::vec3(center[0], center[1], (center[2] + 0.5 * dimensions[2]));

		// The maximum coordinate of the bounding box

		maximum = glm::vec3((center[0] - 0.5 * dimensions[0]), (center[1] + 0.5 * dimensions[1]), center[2]);

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
	else if (Octant == Octants::O4)
	{
		// The minimum coordinate of the bounding box

		minimum = glm::vec3((center[0]+ 0.5 * dimensions[0]), center[1], (center[2] + 0.5 * dimensions[2]));

		// The maximum coordinate of the bounding box

		maximum = glm::vec3(center[0], (center[1] + 0.5 * dimensions[1]), center[2]);

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
	else if (Octant == Octants::O5)
	{
		// The minimum coordinate of the bounding box

		minimum = glm::vec3(center[0], (center[1]-0.5*dimensions[1]), center[2]);

		// The maximum coordinate of the bounding box

		maximum = glm::vec3((center[0] - 0.5 * dimensions[0]), center[1], (center[2] - 0.5 * dimensions[2]));

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
	else if (Octant == Octants::O6)
	{
		// The minimum coordinate of the bounding box

		minimum = glm::vec3((center[0] + 0.5 * dimensions[0]), (center[1] - 0.5 * dimensions[1]), center[2]);

		// The maximum coordinate of the bounding box

		maximum = glm::vec3(center[0], center[1], (center[2] - 0.5 * dimensions[2]));

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
	else if (Octant == Octants::O7)
	{
		// The minimum coordinate of the bounding box

		minimum = glm::vec3(center[0], (center[1] - 0.5 * dimensions[1]), (center[2] + 0.5 * dimensions[2]));

		// The maximum coordinate of the bounding box

		maximum = glm::vec3((center[0] - 0.5 * dimensions[0]), center[1], center[2]);

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
	else if (Octant == Octants::O8)
	{
		// The minimum coordinate of the bounding box

		minimum = glm::vec3((center[0] + 0.5 * dimensions[0]), (center[1] - 0.5 * dimensions[1]), (center[2] + 0.5 * dimensions[2]));

		// The maximum coordinate of the bounding box

		maximum = glm::vec3(center[0], center[1], center[2]);

		// Updating the given bounding box

		BoundingBox.Update(minimum, maximum);

		return;
	}
}

template<typename T, size_t MaxDepth>
bool Octree<T, MaxDepth>::IsLeafNode(void)
{
	return m_IsLeafNode;
}

template<typename T, size_t MaxDepth>
bool Octree<T, MaxDepth>::Subdivide(void)
{
	/*
	* Checking exit conditions
	*/

	// If is a leaf node or the maximum depth has beed aproached

	if (!IsLeafNode())
	{
		return false;
	}
	else if (m_Depth+1 == m_MaxDepth)
	{
		// The tree is ready to be filled with data

		m_TreeBuilt = true;

		return false;
	}

	/*
	*  Calculating the needed dimensions
	*/

	glm::vec3 dimensions = m_Position.Dimensions();

	// Safety checking the dimensions so the tree will eventually stop growing

	for (int i = 0; i < 3; i++)
	{
		if (dimensions[i] < MINIMUM_DIMENSION) return false;
	}

	std::cout << "Dimensions are: " << dimensions[0] << ", " << dimensions[1] << ", " << dimensions[2] << "\n";

	/*
	* Creating the coordinates of the Octants, I am using a clever little technique,
	* by shifting bit-wise a number one, I achieve the needed enum class members values,
	* that allows to correctly recognize Octants based on their hex code.
	*/

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		CalculateOctantBounds(m_OctantsBounds[i], static_cast<Octants>(1<<i));
	}

	// Creating the Octants themselves

	m_IsLeafNode = false;

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		m_Octants[i] = std::make_shared<Octree<T, MaxDepth>>(m_OctantsBounds[i], m_Depth+1);
	}
}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::search(const AABB& area, std::list<typename T>& items)
{
	//TODO: Nie do koñca rozumiem ten moment. 

	//Checking the parent node for the items
	if (area->Overlaps(m_Position))
	{
		for (const auto& p : m_Items)
		{
			items.push_back(p);
		}
	}

	//Checking the child nodes
	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
	{
		if (m_Octants[i])
		{
			
			//Checking whether the area contains this child in it
			if (area.Contains(m_OctantsBounds[i]))
			{
				//If so, then I can take all of the content of the nex children
				m_Octants[i]->Items(items);
			}

			//Checking for overlapping
			else if (m_OctantsBounds[i].Overlaps(area))
			{
				m_Octants[i]->search(area, items);
			}
		}
	}
}

template<typename T, size_t MaxDepth>
void Octree<T, MaxDepth>::Items(std::list<typename T>& items)
{
	for (const auto& p : m_Items)
		items.push_back(p);

	for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		if (m_Octants[i]) m_Octants[i]->Items(items);
}