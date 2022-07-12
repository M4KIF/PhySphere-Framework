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

	template<typename T, typename Y>
	class ContainedOctree
	{

		using OctreeContainer = std::list<std::pair<T, Y>>;

	protected:

		Octree<typename OctreeContainer::iterator, Y> m_Root;
		OctreeContainer m_Items;

	public:

		/*
		* Initialisation
		*/

		ContainedOctree();
		ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth);
		ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth, std::list<std::pair<T, Y>> Items);
		~ContainedOctree();

		/*
		* Capacity
		*/

		Collisions::AABB& aabb();
		size_t size();
		size_t max_size();
		size_t max_depth();
		void resize(glm::vec3 minimum, glm::vec3 maximum);
		bool empty();

		/*
		* Element access
		*/

		//Iterators that enable using this container in a for loop(optional)
		typename std::list<std::pair<T, Y>>::iterator begin();
		typename std::list<std::pair<T, Y>>::iterator end();
		typename std::list<std::pair<T, Y>>::iterator cbegin();
		typename std::list<std::pair<T, Y>>::iterator cend();

		//Search functions
		void dfs(Collisions::AABB& area, typename std::list<std::pair<T, Y>>::iterator& items);
		void bfs(Collisions::AABB& area, typename std::list<std::pair<T, Y>>::iterator& items);
		bool contains(Collisions::AABB& area);

		/*
		* Modifiers
		*/

		void insert(std::pair<T, Y> object, Collisions::AABB area);
		void clear();

		/*
		* Space altering
		*/

		void move(Direction dir, size_t distance); //TODO

	};


	/*
	* ///////////////////////
	* /		Definitions     /
	* ///////////////////////
	*/


	template<typename T, typename Y>
	ContainedOctree<T, Y>::ContainedOctree() :
		m_Root()
	{}
	

	template<typename T, typename Y>
	ContainedOctree<T, Y>::ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth) :
		m_Root(BoundingBox, MaxDepth)
	{}


	template<typename T, typename Y>
	ContainedOctree<T, Y>::ContainedOctree(Collisions::AABB BoundingBox, size_t MaxDepth, std::list<std::pair<T, Y>> Items) :
		m_Root(BoundingBox, MaxDepth)
	{
		// TODO: make a bulk insertion algorithm
	}

	template<typename T, typename Y>
	ContainedOctree<T, Y>::~ContainedOctree()
	{
		clear();
	}


	/*////////////////////
	* /     Capacity     /
	*/////////////////////

	template<typename T, typename Y>
	Collisions::AABB& ContainedOctree<T, Y>::aabb()
	{
		return m_Root.aabb();
	}


	template<typename T, typename Y>
	size_t ContainedOctree<T, Y>::size()
	{
		return (size_t)m_Items.size();
	}


	template<typename T, typename Y>
	size_t ContainedOctree<T, Y>::max_size()
	{
		return m_Root.max_size();
	}


	template<typename T, typename Y>
	size_t ContainedOctree<T, Y>::max_depth()
	{
		return m_Root.max_depth();
	}


	template<typename T, typename Y>
	void ContainedOctree<T, Y>::resize(glm::vec3 minimum, glm::vec3 maximum)
	{

		// TODO: Implement it here, after it is completed in the octree with all of the node deleting and moving

	}


	template<typename T, typename Y>
	bool ContainedOctree<T, Y>::empty()
	{
		return m_Items.empty();
	}


	/*////////////////////
	* / Element Access   /
	*/////////////////////


	template<typename T, typename Y>
	typename std::list<std::pair<T, Y>>::iterator ContainedOctree<T, Y>::begin()
	{
		return m_Items.begin();
	}


	template<typename T, typename Y>
	typename std::list<std::pair<T, Y>>::iterator ContainedOctree<T, Y>::end()
	{
		return m_Items.end();
	}


	template<typename T, typename Y>
	typename std::list<std::pair<T, Y>>::iterator ContainedOctree<T, Y>::cbegin()
	{
		return m_Items.cbegin();
	}


	template<typename T, typename Y>
	typename std::list<std::pair<T, Y>>::iterator ContainedOctree<T, Y>::cend()
	{
		return m_Items.cend();
	}


	template<typename T, typename Y>
	void ContainedOctree<T, Y>::dfs(Collisions::AABB& area, typename std::list<std::pair<T, Y>>::iterator& items)
	{
		m_Root.dfs(area, items);
	}


	template<typename T, typename Y>
	void ContainedOctree<T, Y>::bfs(Collisions::AABB& area, typename std::list<std::pair<T, Y>>::iterator& items)
	{
		m_Root.bfs(area, items);
	}


	template<typename T, typename Y>
	bool ContainedOctree<T, Y>::contains(Collisions::AABB& area)
	{
		m_Root.contains(area);
	}


	/*////////////////////
	* /    Modifiers     /
	*/////////////////////


	template<typename T, typename Y>
	void ContainedOctree<T, Y>::insert(std::pair<T, Y> object, Collisions::AABB area)
	{
		//Here I am inserting first into the list
		m_Items.push_back(object);

		//And then I am giving the iterator to the octree and inserting as normal
		m_Root.insert(std::prev(m_Items.end()), area);
	}


	template<typename T, typename Y>
	void ContainedOctree<T, Y>::clear()
	{
		//And the whole Octree
		m_Root.clear();

		//Clears the list of items
		m_Items.clear();
	}


	/*////////////////////
	* /  Space altering  /
	*/////////////////////

	template<typename T, typename Y>
	void ContainedOctree<T, Y>::move(Direction dir, size_t distance)
	{

	}

}
