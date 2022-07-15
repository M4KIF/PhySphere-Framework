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
	struct OctreeItem
	{
		//Item itself
		T item;

		//The location to the container inside Octree that holds the iterator to this exact element above
		ItemLocation<typename std::list<OctreeItem<T>>::iterator> item_position;
	};

	template<typename T>
	class ContainedOctree
	{

		using OctreeContainer = std::list<OctreeItem<T>>;

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

		bool insert(T object, Collisions::AABB area);
		bool remove(typename OctreeContainer::iterator& item);
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
	bool ContainedOctree<T>::insert(T object, Collisions::AABB area)
	{
		//Temporary storage for the itemlocation object
		OctreeItem<T> temp;

		//Inserting the item to the structure
		temp.item = object;

		//Pushing the structure up the list
		m_Items.push_back(temp);

		//Filling the remaining data, that We get from the Octree insertion
		m_Items.back().item_position = m_Root.insert(std::prev(m_Items.end()), area);
	}


	template<typename T>
	bool ContainedOctree<T>::remove(typename OctreeContainer::iterator& item)
	{
		/*Basicly, acceses the iterator, finds the container in the accessed structure,
		finds the iterator in the structure, and demands the container to erase the given iterator from its content*/
		item->item_position.items_container->erase(item->item_position.items_iterator);

		//Deletes the original item from the list
		m_Items.erase(item);
	}


	template<typename T>
	void ContainedOctree<T>::clear()
	{
		//And the whole Octree
		m_Root.clear();

		//Clears the list of items

		//TODO: CLEAR THE NEW STRUCTS BEFORE DELETING

		m_Items.clear();
	}


	/*////////////////////
	* /  Space altering  /
	*/////////////////////

	template<typename T>
	void ContainedOctree<T>::shift(size_t leaf_nodes, Direction direction, std::list<T>& discarded_items, std::list<Collisions::AABB>& free_nodes)
	{
		
	}

}
