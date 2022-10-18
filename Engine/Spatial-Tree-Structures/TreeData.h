#include<list>
#include<AABB.h>

#ifndef TREEDATA_H
#define TREEDATA_H

template<typename T>
struct Location
{
	typename std::list<T>* items_container = nullptr;
	typename std::list<T>::iterator items_iterator;
	typename Collisions::AABB aabb;
};

enum class Directions : unsigned char {
	North = 0x01, // = 0b00000001 -> 1 << 1
	South = 0x02, // = 0b00000010 -> 1 << 2,
	East = 0x04, // = 0b00000100 -> 1 << 3,
	West = 0x08 // = 0b00001000 -> 1 << 4
};

#endif
