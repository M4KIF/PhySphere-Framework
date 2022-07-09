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

	template<typename T, size_t MaxDepth>
	class ContainedOctree
	{

		using OctreeContainer = std::list<T>;

	protected:

		Octree<T, MaxDepth> m_Octree;
		OctreeContainer m_Items;

	public:



	};

}
