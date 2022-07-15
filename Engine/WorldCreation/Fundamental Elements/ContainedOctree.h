#pragma once

//Custom Libraries

//Default Libraries

//Game files
#include<Engine/WorldCreation/Fundamental Elements/Octree.h>


/*
* ////////////////////////////////////
* This container is meant to implement
* the Octree in conjunction with a list
* This way way, the
* Octree will not own any item, but only
* iterators to the items, It's cheaper* 
* /////////////////////////////////////
*/

namespace Octree {

	template<typename T>
	class ContainedOctree
	{

		using OctreeContainer = std::list<T>;

	protected:

		Octree<typename OctreeContainer::iterator> m_Root;
		OctreeContainer m_Items;

	public:

		/*
		* Initialisation
		*/

		ContainedOctree();
		ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth);
		ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth, std::list<T> Items);
		~ContainedOctree();

		/*
		* Capacity
		*/

		Collisions::AABB& aabb();
		size_t size();
		size_t max_size();
		size_t max_depth();
		void resize(Collisions::AABB area);
		bool empty();

		/*
		* Element access
		*/

		//Iterators that enable using this container in a for loop(optional)
		typename std::list<T>::iterator begin();
		typename std::list<T>::iterator end();
		typename std::list<T>::iterator cbegin();
		typename std::list<T>::iterator cend();

		//Search functions
		void dfs(Collisions::AABB& area, typename std::list<T>::iterator& items);
		void bfs(Collisions::AABB& area, typename std::list<T>::iterator& items);
		bool contains(Collisions::AABB& area);

		/*
		* Modifiers
		*/

		void insert(T object, Collisions::AABB area);
		void clear();

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


	template<typename T>
	ContainedOctree<T>::ContainedOctree() :
		m_Root()
	{}
	

	template<typename T>
	ContainedOctree<T>::ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth) :
		m_Root(BoundingBox, MaxDepth)
	{}


	template<typename T>
	ContainedOctree<T>::ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth, std::list<T> Items) :
		m_Root(BoundingBox, MaxDepth)
	{
		// TODO: make a bulk insertion algorithm
	}

	template<typename T>
	ContainedOctree<T>::~ContainedOctree()
	{
		clear();
	}


	/*////////////////////
	* /     Capacity     /
	*/////////////////////

	template<typename T>
	Collisions::AABB& ContainedOctree<T>::aabb()
	{
		return m_Root.aabb();
	}


	template<typename T>
	size_t ContainedOctree<T>::size()
	{
		return (size_t)m_Items.size();
	}


	template<typename T>
	size_t ContainedOctree<T>::max_size()
	{
		return m_Root.max_size();
	}


	template<typename T>
	size_t ContainedOctree<T>::max_depth()
	{
		return m_Root.max_depth();
	}


	template<typename T>
	void ContainedOctree<T>::resize(Collisions::AABB area)
	{
		//Cleaning the tree of the iterators
		m_Root.resize(area);

		//Cleaning the list
		m_Items.clear();
	}


	template<typename T>
	bool ContainedOctree<T>::empty()
	{
		return m_Items.empty();
	}


	/*////////////////////
	* / Element Access   /
	*/////////////////////


	template<typename T>
	typename std::list<T>::iterator ContainedOctree<T>::begin()
	{
		return m_Items.begin();
	}


	template<typename T>
	typename std::list<T>::iterator ContainedOctree<T>::end()
	{
		return m_Items.end();
	}


	template<typename T>
	typename std::list<T>::iterator ContainedOctree<T>::cbegin()
	{
		return m_Items.cbegin();
	}


	template<typename T>
	typename std::list<T>::iterator ContainedOctree<T>::cend()
	{
		return m_Items.cend();
	}


	template<typename T>
	void ContainedOctree<T>::dfs(Collisions::AABB& area, typename std::list<T>::iterator& items)
	{
		m_Root.dfs(area, items);
	}


	template<typename T>
	void ContainedOctree<T>::bfs(Collisions::AABB& area, typename std::list<T>::iterator& items)
	{
		m_Root.bfs(area, items);
	}


	template<typename T>
	bool ContainedOctree<T>::contains(Collisions::AABB& area)
	{
		m_Root.contains(area);
	}


	/*////////////////////
	* /    Modifiers     /
	*/////////////////////


	template<typename T>
	void ContainedOctree<T>::insert(T object, Collisions::AABB area)
	{
		//Here I am inserting first into the list
		m_Items.push_back(object);

		//And then I am giving the iterator to the octree and inserting as normal
		m_Root.insert(std::prev(m_Items.end()), area);
	}


	template<typename T>
	void ContainedOctree<T>::clear()
	{
		//And the whole Octree
		m_Root.clear();

		//Clears the list of items
		m_Items.clear();
	}


	/*////////////////////
	* /  Space altering  /
	*/////////////////////

	template<typename T>
	void ContainedOctree<T>::shift(size_t leaf_nodes, Direction direction, std::list<T>& discarded_items, std::list<Collisions::AABB>& free_nodes)
	{
		//Storing the new coordinates for the tree
		std::array<glm::vec3, 2> bounding_box = m_Root.aabb().bounding_region();

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

		//Resizing the tree
		resize({ bounding_box[0], bounding_box[1] });

		//Iterator of the items list
		typename std::list<T>::iterator it;

		//Bulk inserting the content of the tree
		for (it = items.begin(); it != items.end(); ++it)
		{
			//If the item cannot be inserted, it means that is has been discarded
			if (!insert((*it), (*it).second))
			{
				discarded_items.push_back((*it).first);
				free_nodes.push_back((*it).second);
			}

		}
	}

}
