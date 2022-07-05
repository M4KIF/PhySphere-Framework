#pragma once

// Game Files
#include<Engine/WorldCreation/Fundamental Elements/Block.h>

/*
* Here there are the classes that represent block which are inherited from one main "Block" class,
* they all have the same parameters and the difference lays in the values themselves. This implementation 
* targets the ease of comparing blocks by using typeid.
*/

class Air : public Block {
public:

	// Constructors and a Virtual destructor

	Air(void) : Block({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f }) { m_Toughness = 1; };
	virtual ~Air(void) {};

	// Place for other polimorphic methods

};

class Indestructible : public Block {
public:

	// Constructors and a Virtual destructor

	Indestructible(void) : Block({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f }) {};
	virtual ~Indestructible(void) {};

	// Place for other polimorphic methods

};

class Stone : public Block {
public:

	// Constructors and a Virtual destructor

	Stone(void) : Block({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f }) {};
	virtual ~Stone(void) {};

	// Place for other polimorphic methods

};

class Grass : public Block {
public:

	// Constructors and a Virtual destructor

	Grass(void) : Block({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f }) {};
	virtual ~Grass(void) {};

	// Place for other polimorphic methods

};

class Sand : public Block {
public:

	// Constructors and a Virtual destructor

	Sand(void) : Block({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f }) {};
	virtual ~Sand(void) {};

	// Place for other polimorphic methods

};

class Wood : public Block {
public:

	// Constructors and a Virtual destructor

	Wood(void) : Block({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f }) {};
	virtual ~Wood(void) {};

	// Place for other polimorphic methods

};

class Leaf : public Block {
public:

	// Constructors and a Virtual destructor

	Leaf(void) : Block({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f }) {};
	virtual ~Leaf(void) {};

	// Place for other polimorphic methods

};