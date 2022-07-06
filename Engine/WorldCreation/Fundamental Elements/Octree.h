#pragma once

//Custom Libraries

//Default Libraries
#include<list>
#include<memory>
#include<iostream>

//Game files
#include<Engine/Collisions/AABB.h>

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

namespace Octree {

	template<typename T, size_t MaxDepth>
	class Octree
	{
		/*
		* Place for the aliases,
		* private member functions
		* and other expression
		*/

		//Alias for the octant coordinates
		using OctantBoxes = std::array<Collisions::AABB, 8>;

		//Trick for storing the data about Octants
		enum class Octants : unsigned char {
			O1 = 0x01, // = 0b00000001 -> 1 << 1
			O2 = 0x02, // = 0b00000010 -> 1 << 2
			O3 = 0x04, // = 0b00000100 -> 1 << 3
			O4 = 0x08, // = 0b00001000 -> 1 << 4
			O5 = 0x10, // = 0b00010000 -> 1 << 5
			O6 = 0x20, // = 0b00100000 -> 1 << 6
			O7 = 0x40, // = 0b01000000 -> 1 << 7
			O8 = 0x80  // = 0b10000000 -> 1 << 8
		};

		//Intelligently calculates the BB's for all needed octants
		void calculate_bounding_box(Collisions::AABB& BoundingBox, Octants Octant);

		//Return true only if the Octants array has nullptrs in it
		bool is_leaf_node(void);

		//Recursively comes down till the depth reaches maximum
		void subdivide(void);

		//Recursive search function
		void search(const Collisions::AABB& area, std::list<typename T>& items);

		//Pushes all of the items from the node
		void items(std::list<typename T>& items);

	protected:

		// The area that the Octree contains
		Collisions::AABB m_Position;

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
		bool m_IsLeaf = false;
		bool m_NodeReady = false;
		bool m_ContainsItem = false;

		//Item that the node is storing. Can become anything that the programmer wants it to
		T m_Item;

	public:

		/*
		* Initialisation
		*/

		Octree();
		Octree(Collisions::AABB BoundingBox);
		Octree(Collisions::AABB BoundingBox, size_t Depth);
		Octree(Collisions::AABB BoundingBox, size_t Depth, std::list<std::shared_ptr<T>> Items);
		~Octree();

		/*
		* Capacity
		*/

		size_t size();
		size_t max_size();
		size_t depth();
		size_t max_depth();
		void resize(glm::vec3 minimum, glm::vec3 maximum);
		bool empty();

		/*
		* Element access
		*/

		std::list<T> search(const Collisions::AABB& area);
		bool contains(const Collisions::AABB& area);


		/*
		* Modifiers
		*/

		void insert(T object, Collisions::AABB area);
		void insert_to_level(T object, Collisions::AABB area, size_t level);
		void clear();

		/*
		* Space altering
		*/

		void shift();

	};



	/*
	* ///////////////////////
	* /		Definitions     /
	* ///////////////////////
	*/



	//Defatult Constructor
	template<typename T, size_t MaxDepth>
	Octree<T, MaxDepth>::Octree()
	{
		// Does nothing, because the Octree doesn't have the bounding space defined
	}


	//Area setting constructor, should be always first
	template<typename T, size_t MaxDepth>
	Octree<T, MaxDepth>::Octree(Collisions::AABB BoundingBox) :
		m_Position(BoundingBox)
	{
		// Every octree starts as a leaf node before any subdivisions

		m_IsLeaf = true;
		m_NodeReady = true;

		// Proceeds to subdivision

		subdivide();
	}


	//Area setting constructor, that takes a depth param, used in subdivision
	template<typename T, size_t MaxDepth>
	Octree<T, MaxDepth>::Octree(Collisions::AABB BoundingBox, size_t Depth) :
		m_Position(BoundingBox), m_Depth(Depth)
	{
		// Every octree starts as a leaf node before any subdivisions

		m_IsLeaf = true;
		m_NodeReady = true;

		// Sets the current level

		m_Depth = Depth;

		// Proceeds to subdivision

		subdivide();
	}


	//
	template<typename T, size_t MaxDepth>
	Octree<T, MaxDepth>::~Octree()
	{
		//Default
	}



	/*
	* Capacity
	*/



	template<typename T, size_t MaxDepth>
	size_t Octree<T, MaxDepth>::size()
	{
		size_t count;

		//Checks if the item is allocated
		if (m_Item)
		{
			//If yes, then adds one to count
			count++;
		}

		//Iterates recursively through all of the octants
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			if (m_Octants[i])
			{
				count += m_Octants[i]->size();
			}
		}

		//Returns the final value and recursive iteration values
		return count;
	}


	template<typename T, size_t MaxDepth>
	size_t Octree<T, MaxDepth>::max_size()
	{
		//Returns a theoretical maximum size, which equals to the maximum possible nodes
		return std::pow(8, m_MaxDepth);
	}


	template<typename T, size_t MaxDepth> inline
		size_t Octree<T, MaxDepth>::depth()
	{
		return m_Depth;
	}


	template<typename T, size_t MaxDepth> inline
		size_t Octree<T, MaxDepth>::max_depth()
	{
		return m_MaxDepth;
	}


	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::resize(glm::vec3 minimum, glm::vec3 maximum)
	{
		// Resizing invalids the whole tree
		clear();

		// Actual resizing of the structure
		m_Position.update(minimum, maximum);

		// Calcaulating the potential children coordinates
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			CalculateOctantBounds(m_OctantsBounds[i], static_cast<Octants>(1 << i));
		}
	}


	template<typename T, size_t MaxDepth>
	bool Octree<T, MaxDepth>::empty()
	{
		//If there are no Octants in the root node, then the tree is empty
		if (!m_Octants[0]) return true;
	}



	/*
	* Element Access
	*/



	//Searches for a given area inside the tree
	template<typename T, size_t MaxDepth>
	std::list<T> Octree<T, MaxDepth>::search(const Collisions::AABB& area)
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


	//Checks whether the tree contains a certain area
	template<typename T, size_t MaxDepth>
	bool Octree<T, MaxDepth>::contains(const Collisions::AABB& area)
	{
		return m_Position.contains(area);
	}



	/*
	* Modifiers
	*/



	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::insert(T object, Collisions::AABB area)
	{
		// Checking whether anything can be inserted
		if (!m_NodeReady)
		{
			std::cout << "Here?\n";
			return;
		}

		// Checking whether the children can contain the item
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			if (m_Octants[i]->contains(area))
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
					m_Octants[i]->insert(object, area);

					return;
				}
			}

		}

		//It must be somewhere in the tree, so
		std::cout << "MAMY ITEM" << m_Item << "\n\n";
		m_Item = object;
	}


	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::insert_to_level(T object, Collisions::AABB area, size_t level)
	{

	}


	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::clear()
	{
		// Clearing the containts of the pointer inside the node

		m_ContainsItem = false;

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



	/*
	* Space altering
	*/



	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::shift()
	{

	}



	/*
	* //////////////////////////////
	* /  Private member functions  /
	* //////////////////////////////
	*/



	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::calculate_bounding_box(Collisions::AABB& BoundingBox, Octants Octant)
	{
		// Here is the center of the parent node Octree

		glm::vec3 center = m_Position.center();

		// And It's side length for all dimensions

		glm::vec3 dimensions = m_Position.dimensions();

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

			BoundingBox.update(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O2)
		{
			// The minimum coordinate of the bounding box

			minimum = glm::vec3((center[0] + 0.5 * dimensions[0]), center[1], center[2]);

			// The maximum coordinate of the bounding box

			maximum = glm::vec3(center[0], (center[1] + 0.5 * dimensions[1]), (center[2] - 0.5 * dimensions[2]));

			// Updating the given bounding box

			BoundingBox.update(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O3)
		{
			// The minimum coordinate of the bounding box

			minimum = glm::vec3(center[0], center[1], (center[2] + 0.5 * dimensions[2]));

			// The maximum coordinate of the bounding box

			maximum = glm::vec3((center[0] - 0.5 * dimensions[0]), (center[1] + 0.5 * dimensions[1]), center[2]);

			// Updating the given bounding box

			BoundingBox.update(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O4)
		{
			// The minimum coordinate of the bounding box

			minimum = glm::vec3((center[0] + 0.5 * dimensions[0]), center[1], (center[2] + 0.5 * dimensions[2]));

			// The maximum coordinate of the bounding box

			maximum = glm::vec3(center[0], (center[1] + 0.5 * dimensions[1]), center[2]);

			// Updating the given bounding box

			BoundingBox.update(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O5)
		{
			// The minimum coordinate of the bounding box

			minimum = glm::vec3(center[0], (center[1] - 0.5 * dimensions[1]), center[2]);

			// The maximum coordinate of the bounding box

			maximum = glm::vec3((center[0] - 0.5 * dimensions[0]), center[1], (center[2] - 0.5 * dimensions[2]));

			// Updating the given bounding box

			BoundingBox.update(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O6)
		{
			// The minimum coordinate of the bounding box

			minimum = glm::vec3((center[0] + 0.5 * dimensions[0]), (center[1] - 0.5 * dimensions[1]), center[2]);

			// The maximum coordinate of the bounding box

			maximum = glm::vec3(center[0], center[1], (center[2] - 0.5 * dimensions[2]));

			// Updating the given bounding box

			BoundingBox.update(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O7)
		{
			// The minimum coordinate of the bounding box

			minimum = glm::vec3(center[0], (center[1] - 0.5 * dimensions[1]), (center[2] + 0.5 * dimensions[2]));

			// The maximum coordinate of the bounding box

			maximum = glm::vec3((center[0] - 0.5 * dimensions[0]), center[1], center[2]);

			// Updating the given bounding box

			BoundingBox.update(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O8)
		{
			// The minimum coordinate of the bounding box

			minimum = glm::vec3((center[0] + 0.5 * dimensions[0]), (center[1] - 0.5 * dimensions[1]), (center[2] + 0.5 * dimensions[2]));

			// The maximum coordinate of the bounding box

			maximum = glm::vec3(center[0], center[1], center[2]);

			// Updating the given bounding box

			BoundingBox.update(minimum, maximum);

			return;
		}
	}


	template<typename T, size_t MaxDepth>
	bool Octree<T, MaxDepth>::is_leaf_node(void)
	{
		return m_IsLeaf;
	}


	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::subdivide(void)
	{
		/*
		* Checking exit conditions
		*/

		// If is a leaf node or the maximum depth has beed aproached
		if (!is_leaf_node())
		{
			return;
		}
		else if (m_Depth + 1 > m_MaxDepth)
		{
			return;
		}

		/*
		*  Calculating the needed dimensions
		*/

		glm::vec3 dimensions = m_Position.dimensions();

		// Safety checking the dimensions so the tree will eventually stop growing
		for (int i = 0; i < 3; i++)
		{
			if (dimensions[i] < MINIMUM_DIMENSION) return;
		}

		std::cout << "Dimensions are: " << dimensions[0] << ", " << dimensions[1] << ", " << dimensions[2] << "\n";

		/*
		* Creating the coordinates of the Octants, I am using a clever little technique,
		* by shifting bit-wise a number one, I achieve the needed enum class members values,
		* that allows to correctly recognize Octants based on their hex code.
		*/

		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			calculate_bounding_box(m_OctantsBounds[i], static_cast<Octants>(1 << i));
		}

		// Creating the Octants themselves

		m_IsLeaf = false;

		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			m_Octants[i] = std::make_shared<Octree<T, MaxDepth>>(m_OctantsBounds[i], m_Depth + 1);
		}
	}


	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::search(const Collisions::AABB& area, std::list<typename T>& items)
	{
		//TODO: Nie do koñca rozumiem ten moment. 

		//Checking the parent node for the items
		if (m_ContainsItem)
		{
			if (area.overlaps(m_Position))
			{
				items.push_back(m_Item);
			}
		}


		//Checking the child nodes
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			if (m_Octants[i])
			{

				//Checking whether the area contains this child in it
				if (area.contains(m_OctantsBounds[i]))
				{
					//If so, then I can take all of the content of the nex children
					m_Octants[i]->items(items);
				}

				//Checking for overlapping
				else if (m_OctantsBounds[i].overlaps(area))
				{
					m_Octants[i]->search(area, items);
				}
			}
		}
	}


	template<typename T, size_t MaxDepth>
	void Octree<T, MaxDepth>::items(std::list<typename T>& items)
	{
		items.push_back(m_Item);

		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
			if (m_Octants[i]) m_Octants[i]->items(items);
	}

}