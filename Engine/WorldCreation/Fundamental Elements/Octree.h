#pragma once

//Custom Libraries

//Default Libraries
#include<list>
#include<queue>
#include<memory>
#include<iostream>
#include<algorithm>

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

enum class Direction :unsigned char {
	North = 0x01, // = 0b00000001 -> 1 << 1
	South = 0x02, // = 0b00000010 -> 1 << 2,
	East = 0x04, // = 0b00000100 -> 1 << 3,
	West = 0x08 // = 0b00001000 -> 1 << 4
};

namespace Octree {

	template<typename T>
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

		//Speaks for itself
		bool is_leaf_node(void);

		//Deletes the nodes that went out of bounds
		void delete_nodes(std::pair<std::list<T>, Direction> result, size_t starting_level);

		//Moves the rest of the octants according to the direction that has been deleted.
		void move_nodes(Collisions::AABB& area, Direction direction);

		//
		std::array<std::shared_ptr<Octree<T>>, 8>& access_octants();

		//
		void collect_items(std::list<std::pair<T, Collisions::AABB>>& items);

		//Set of minimal recursive functions that just do their tasks, without tree safety
		void recursive_subdivide(void); //OK
		void recursive_dfs(Collisions::AABB& area, std::list<T>& items); //OK
		bool recursive_insert(T object, Collisions::AABB area); //OK
		void recursive_resize(Collisions::AABB& area); //OK


	protected:

		//The dimensions of the tree
		Collisions::AABB m_Position;
		float m_LeafNodeSide;

		// Depth checking
		size_t m_MaxDepth;
		size_t m_Depth = 0;

		// A clever way of knowing whether the Octants are active
		// if the value is shifted 8 times to the left, that means, that all of the octants have been set
		unsigned char m_ActiveOctants;

		// The bounds of the potential Octants
		OctantBoxes m_OctantsBounds;

		// The Octants themselves, will be made with the use of a bounds calulating function
		std::array<std::shared_ptr<Octree<T>>, 8> m_Octants;

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
		Octree(Collisions::AABB BoundingBox, size_t MaxDepth);
		Octree(Collisions::AABB BoundingBox, size_t MaxDepth, size_t Depth);
		Octree(Collisions::AABB BoundingBox, size_t MaxDepth, std::list<std::shared_ptr<T>> Items);
		~Octree();

		/*
		* Capacity
		*/

		Collisions::AABB& aabb();
		OctantBoxes octants_positions();
		size_t size(); //OK
		size_t max_size(); //OK
		size_t depth(); //OK
		size_t max_depth(); //OK
		void resize(Collisions::AABB area);
		bool empty(); //OK

		/*
		* Element access
		*/

		void dfs(Collisions::AABB& area, std::list<T>& items); //TODO
		void bfs(Collisions::AABB& area, std::list<T>& items); //TODO
		bool contains(Collisions::AABB& area); //OK
		void erase(Collisions::AABB& area, std::list<T>& items);
		T access_element();

		/*
		* Modifiers
		*/

		bool insert(T object, Collisions::AABB area); //OK
		void clear(); //OK 

		/*
		* Space altering
		*/

		void shift(size_t leaf_nodes, Direction direction, std::list<T>& discarded_items, std::list<Collisions::AABB>& free_nodes); //TODO
	};


	/*
	* ///////////////////////
	* /		Definitions     /
	* ///////////////////////
	*/


	//Default Constructor
	template<typename T>
	Octree<T>::Octree()
	{
		// Does nothing, because the Octree doesn't have the bounding space defined
	}


	//Area setting constructor, should be always first
	template<typename T>
	Octree<T>::Octree(Collisions::AABB BoundingBox, size_t MaxDepth) :
		m_Position(BoundingBox)
	{
		//Setting max depth available for the Tree
		m_MaxDepth = MaxDepth;

		//Calculating the side length
		m_LeafNodeSide = m_Position.dimensions().x / std::pow(2.0, m_MaxDepth);

		//Every octree starts as a leaf node before any subdivisions
		m_IsLeaf = true;
		m_NodeReady = true;
		m_ContainsItem = false;

		//Proceeds to subdivision
		recursive_subdivide();
	}


	//Area setting constructor, that takes a depth param, used in subdivision
	template<typename T>
	Octree<T>::Octree(Collisions::AABB BoundingBox, size_t MaxDepth, size_t Depth) :
		m_Position(BoundingBox), m_Depth(Depth)
	{
		//Every octree starts as a leaf node before any subdivisions
		m_IsLeaf = true;
		m_NodeReady = true;
		m_ContainsItem = false;

		//Sets the current level
		m_Depth = Depth;
		m_MaxDepth = MaxDepth;

		//Calculating the side length
		m_LeafNodeSide = m_Position.dimensions().x / std::pow(2.0, m_MaxDepth);

		//Proceeds to subdivision
		recursive_subdivide();
	}


	//
	template<typename T>
	Octree<T>::~Octree()
	{}


	/*////////////////////
	* /     Capacity     /
	*/////////////////////


	template<typename T>
	Collisions::AABB& Octree<T>::aabb()
	{
		return m_Position;
	}


	template<typename T>
	std::array<Collisions::AABB, 8> Octree<T>::octants_positions()
	{
		return m_OctantsBounds;
	}


	template<typename T>
	size_t Octree<T>::size()
	{
		size_t count = 0;

		//Checks if the item is allocated
		if (m_ContainsItem)
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


	template<typename T>
	size_t Octree<T>::max_size()
	{
		//Returns a theoretical maximum size, which equals to the maximum possible nodes
		return std::pow(NUMBER_OF_OCTANTS, m_MaxDepth);
	}


	template<typename T> inline
		size_t Octree<T>::depth()
	{
		return m_Depth;
	}


	template<typename T> inline
		size_t Octree<T>::max_depth()
	{
		return m_MaxDepth;
	}


	template<typename T>
	void Octree<T>::resize(Collisions::AABB area)
	{
		//All of the data has to be invalidated
		clear();

		//And the tree has to be built a new
		recursive_resize(area);
	}


	template<typename T>
	bool Octree<T>::empty()
	{
		//If there are no Octants in the root node, then the tree is empty
		if (!m_Octants[0]) return true;
	}


	/*////////////////////
	* / Element Access   /
	*/////////////////////


	//Searches for a given area inside the tree
	template<typename T>
	void Octree<T>::dfs(Collisions::AABB& area, std::list<T>& items)
	{
		//This can go deep into the recursion
		recursive_dfs(area, items);
	}


	//Searches for a given area inside the tree
	template<typename T>
	void Octree<T>::bfs(Collisions::AABB& area, std::list<T>& items)
	{
		//Lamda for asigning the children to the queue
		auto asign_children = [](std::list<std::shared_ptr<Octree<T>>>& temp_queue, std::array<std::shared_ptr<Octree<T>>, 8>& temp) {
			//Pushing the octants to a temporary container
			for (uint8_t j = 0; j < NUMBER_OF_OCTANTS; ++j)
			{
				if (temp[j])
				{
					//If the pointer isn't null, I am placing it on to the queue
					temp_queue.push_back(temp[j]);
				}
				else
				{
					//Else I tell the function, that We propably reached the leaf node
					return false;
				}

			}

			//Comes down here when every octant has been found and pushed to the queue
			return true;
		};

		//Contains the main working queue
		std::list<std::shared_ptr<Octree<T>>> octants;

		//Checking if the root contains the item
		if (m_ContainsItem)
		{
			//Adding an item if it fits the octree, or items if they cross through trees
			if (area.contains(m_Position))
			{
				items.push_back(m_Item);
			}
		}

		//Placing the root octants to the queue
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			if (m_Octants[i])
				octants.push_back(m_Octants[i]);
		}

		//Iterative breadth first search implementation for an octree
		size_t CurrentDepth = m_Depth;

		while (CurrentDepth < m_MaxDepth)
		{
			//Setting current depth
			CurrentDepth++;

			//For building the next octants queue
			std::list<std::shared_ptr<Octree<T>>> lower_octants;

			typename std::list<std::shared_ptr<Octree<T>>>::iterator it;

			//Using a Lambda, that enables returning only from the 2 nested loops
			[&] {
				//Checking the list
				for (it = octants.begin(); it!=octants.end(); ++it)
				{
					//Take the AABB of the octant
					Collisions::AABB comparing = (**it).aabb();

					std::array<glm::vec3, 2> test = comparing.bounding_region();

					//Compare with the given area
					if (comparing.intersect2(area)) {

						//Adding an item if it fits the octree, or items if they cross through trees
						if (area.contains(comparing))
						{
							items.push_back((**it).access_element());
						}
						else if (is_leaf_node() && comparing.intersect2(area))
						{
							items.push_back((**it).access_element());
						}

					}

					//If the tree reached leaf nodes, this fails
					if (!asign_children(lower_octants, (**it).access_octants()))
					{
						return;
					}
				}
			}();

			//Swaping the queues
			std::swap(octants, lower_octants);
		}
	}


	//Checks whether the tree contains a certain area
	template<typename T>
	bool Octree<T>::contains(Collisions::AABB& area)
	{
		return m_Position.contains(area);
	}


	template<typename T>
	void Octree<T>::erase(Collisions::AABB& area, std::list<T>& items)
	{
		//Checking the parent node for the items
		if (m_ContainsItem)
		{
			//Adding an item if it fits the octree, or items if they cross through trees
			if (area.contains(m_Position))
			{
				//Unchecking the flag
				m_ContainsItem = false;

				//Pushing the found item into the list
				items.push_back(m_Item);
			}
			else if (is_leaf_node() && m_Position.intersect2(area))
			{
				//Unchecking the flag
				m_ContainsItem = false;

				//Pushing the found item into the list
				items.push_back(m_Item);
			}
		}

		//Checking the child nodes
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			if (m_Octants[i])
			{
				//Checking for overlapping
				if (m_OctantsBounds[i].intersect2(area))
				{
					m_Octants[i]->erase(area, items);
				}
			}
		}

	}


	template<typename T>
	T Octree<T>::access_element()
	{
		return m_Item;
	}


	/*////////////////////
	* /    Modifiers     /
	*/////////////////////


	template<typename T>
	bool Octree<T>::insert(T object, Collisions::AABB area)
	{
		//Checking whether anything can be inserted
		if (!m_NodeReady)
		{
			return false;
		}

		//
		return recursive_insert(object, area);

	}


	template<typename T>
	void Octree<T>::clear()
	{
		//Enabling the user to write a top-down new tree, by removing the locking flags
		m_ContainsItem = false;

		//Proceeding to the Octants
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{

			if (m_Octants[i])
			{
				// Recursively cleaning
				m_Octants[i]->clear();
			}
		}
	}


	/*////////////////////
	* /  Space altering  /
	*/////////////////////


	template<typename T>
	void Octree<T>::shift(size_t leaf_nodes, Direction direction, std::list<T>& discarded_items, std::list<Collisions::AABB>& free_nodes)
	{
		//Storing the new coordinates for the tree
		std::array<glm::vec3, 2> bounding_box = m_Position.bounding_region();

		//Temporary items list
		std::list<std::pair<T, Collisions::AABB>> items;

		//Calculating the bounding box
		switch (direction)
		{
		case Direction::North:

			bounding_box[0].z -= leaf_nodes * m_LeafNodeSide;
			bounding_box[1].z -= leaf_nodes * m_LeafNodeSide;

			break;
		case Direction::South:
			
			bounding_box[0].z += leaf_nodes * m_LeafNodeSide;
			bounding_box[1].z += leaf_nodes * m_LeafNodeSide;

			break;
		case Direction::East:

			bounding_box[0].x += leaf_nodes * m_LeafNodeSide;
			bounding_box[1].x += leaf_nodes * m_LeafNodeSide;

			break;
		case Direction::West:
			
			bounding_box[0].x -= leaf_nodes * m_LeafNodeSide;
			bounding_box[1].x -= leaf_nodes * m_LeafNodeSide;

			break;
		}

		//Placing all of the contained items into a list of pairs(item + coordinates)
		collect_items(items);

		//Resizing the tree
		resize({ bounding_box[0], bounding_box[1] });

		//Iterator of the items list
		typename std::list<std::pair<T, Collisions::AABB>>::iterator it;

		//Bulk inserting the content of the tree
		for (it = items.begin(); it!=items.end(); ++it)
		{
			//If the item cannot be inserted, it means that is has been discarded
			if (!insert((*it).first, (*it).second))
			{
				discarded_items.push_back((*it).first);
				free_nodes.push_back((*it).second);
			}

		}

		//Clearing the temporary items list
		items.clear();


		////Here are the resulting lists
		//std::list<T> deleted_items;
		//std::list<Collisions::AABB> free_nodes;

		////The areas to be edited
		//Collisions::AABB deletion_area;


		////Determines wheteher I have to access the item, or shift a whole node
		//size_t shifting_depth;

		//for (int i = 0; i < m_MaxDepth; i++)
		//{
		//	if ((int)std::log2(m_LeafNodeSide * leaf_nodes) == (int)std::log2(m_Position.dimensions().x / std::pow(2.0, i)))
		//	{
		//		shifting_depth = i;
		//	}
		//}

		////Now as I know which level exactly has to be altered, i shall proceed to the recursive(?) delete function

		////Containts of the pair to be returned
		//std::list<T> deleted_nodes;
		//std::list<Collisions::AABB> free_nodes;

		////I have to delete those nodes, that got out of bounds
		////delete_nodes(results, area);

		////If the delete function gave back some items, then I can set the flag to true
		////if (!results.first.empty())
		//	//results.second = true;

		////And then move the remaining ones to the correct positions
		////move_nodes(area, results.second)
	}


	/*
	* //////////////////////////////
	* /  Private member functions  /
	* //////////////////////////////
	*/


	template<typename T>
	void Octree<T>::calculate_bounding_box(Collisions::AABB& BoundingBox, Octants Octant)
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
			minimum = glm::vec3(center.x - 0.5 * dimensions.x, center.y, center.z);

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x, center.y + 0.5 * dimensions.y, center.z - 0.5 * dimensions.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O2)
		{
			// The minimum coordinate of the bounding box
			minimum = center;

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x+0.5*dimensions.x, center.y + 0.5 * dimensions.y, center.z - 0.5 * dimensions.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O3)
		{
			// The minimum coordinate of the bounding box
			minimum = glm::vec3(center.x - 0.5 * dimensions.x, center.y, center.z + 0.5 * dimensions.z);

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x, center.y + 0.5 * dimensions.y, center.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O4)
		{
			// The minimum coordinate of the bounding box
			minimum = glm::vec3(center.x, center.y, center.z + 0.5 * dimensions.z);

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x + 0.5 * dimensions.x, center.y + 0.5 * dimensions.y, center.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O5)
		{
			// The minimum coordinate of the bounding box
			minimum = glm::vec3(center.x - 0.5 * dimensions.x, center.y - 0.5 * dimensions.y, center.z);

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x, center.y, center.z - 0.5 * dimensions.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O6)
		{
			// The minimum coordinate of the bounding box
			minimum = glm::vec3(center.x, center.y-0.5*dimensions.y, center.z);

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x + 0.5 * dimensions.x, center.y, center.z - 0.5 * dimensions.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O7)
		{
			// The minimum coordinate of the bounding box
			minimum = glm::vec3(center.x - 0.5 * dimensions.x, center.y - 0.5 * dimensions.y, center.z + 0.5 * dimensions.z);

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x, center.y, center.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}
		else if (Octant == Octants::O8)
		{
			// The minimum coordinate of the bounding box
			minimum = glm::vec3(center.x, center.y - 0.5 * dimensions.y, center.z + 0.5 * dimensions.z);

			// The maximum coordinate of the bounding box
			maximum = glm::vec3(center.x + 0.5 * dimensions.x, center.y, center.z);

			// Updating the given bounding box
			BoundingBox.update_position(minimum, maximum);

			return;
		}

	}


	template<typename T>
	bool Octree<T>::is_leaf_node(void)
	{
		return m_IsLeaf;
	}


	template<typename T>
	std::array<std::shared_ptr<Octree<T>>, 8>& Octree<T>::access_octants()
	{
		return m_Octants;
	}

	template<typename T>
	void Octree<T>::collect_items(std::list<std::pair<T, Collisions::AABB>>& items)
	{
		if (m_ContainsItem)
		{
			items.push_back({ m_Item, m_Position });
		}
		for (uint8_t i = 0; i < NUMBER_OF_OCTANTS; ++i)
		{
			if(m_Octants[i])
				m_Octants[i]->collect_items(items);
		}
	}


	template<typename T>
	void Octree<T>::recursive_subdivide(void)
	{

		// If is a leaf node or the maximum depth has beed aproached
		if (!is_leaf_node())
		{
			return;
		}
		else if (!(m_Depth <= m_MaxDepth))
		{
			return;
		}

		//Getting the current bb dimensions
		glm::vec3 dimensions = m_Position.dimensions();

		//Safety checking whether the dimensions aren't smaller than the minimum value
		for (int i = 0; i < 3; i++)
		{
			if (dimensions[i] < MINIMUM_DIMENSION) return;
		}

		/*
		* Creating the coordinates of the Octants, I am using a clever little technique,
		* by shifting bit-wise a number one, I achieve the needed enum class members values,
		* that allows to correctly recognize Octants based on their hex code.
		*/

		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			calculate_bounding_box(m_OctantsBounds[i], static_cast<Octants>(1 << i));
		}

		//If it came down here It can't be a leaf node
		m_IsLeaf = false;

		//Creating the octants octrees
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			m_Octants[i] = std::make_shared<Octree<T>>(m_OctantsBounds[i], m_MaxDepth, m_Depth + 1);
		}

	}


	template<typename T>
	void Octree<T>::recursive_dfs(Collisions::AABB& area, std::list<T>& items)
	{
		//Checking the parent node for the items
		if (m_ContainsItem)
		{
			//Adding an item if it fits the octree, or items if they cross through trees
			if (m_Position.contains(area))
			{
				items.push_back(m_Item);
			}
			else if (is_leaf_node() && m_Position.intersect2(area))
			{
				items.push_back(m_Item);
			}
		}

		//Checking the child nodes
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			if (m_Octants[i])
			{
				//Checking for overlapping
				if (m_OctantsBounds[i].intersect2(area))
				{
					m_Octants[i]->recursive_dfs(area, items);
				}
			}
		}

	}

	template<typename T>
	bool Octree<T>::recursive_insert(T object, Collisions::AABB area)
	{
		//Checking whether the children can contain the item
		for (int i = 0; i < NUMBER_OF_OCTANTS; i++)
		{
			if (m_OctantsBounds[i].contains(area))
			{
				//std::cout << "NEIN!\n";
				// Within the depth limit?
				if (m_Depth <= m_MaxDepth)
				{
					//If yes, does the child exist?
					if (!m_Octants[i])
					{
						//If no, create that child
						m_Octants[i] = std::make_shared<Octree<T>>(m_OctantsBounds[i], m_Depth + 1);
					}
					//If yes, proceed to the insertion
					return m_Octants[i]->recursive_insert(object, area);
				}

			}

		}

		//Inserting an item
		if (!m_ContainsItem)
		{
			if (m_Position.contains(area))
			{
				m_Item = object;
				m_ContainsItem = true;

				//returning
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}


	template<typename T>
	void Octree<T>::recursive_resize(Collisions::AABB& area)
	{
		//Taking the bounds from the aabb
		std::array<glm::vec3, 2> bounds = area.bounding_region();
		m_Position.update_position(bounds[0], bounds[1]);
		m_ContainsItem = false;

		// Calcaulating the potential children coordinates
		for (uint8_t i = 0; i < NUMBER_OF_OCTANTS; ++i)
		{
			calculate_bounding_box(m_OctantsBounds[i], (Octants)(1 << i));

		}

		for (uint8_t i = 0; i < NUMBER_OF_OCTANTS; ++i)
		{
			//Updating the octants with the bb data pulled from pre-calculated octantbounds
			if (m_Octants[i])
				m_Octants[i]->recursive_resize(m_OctantsBounds[i]);
		}

	}

}