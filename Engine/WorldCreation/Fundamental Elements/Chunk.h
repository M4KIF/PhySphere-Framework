#pragma once

// Custom Libraries
#include<Libraries/GLM/gtc/matrix_transform.hpp>

// Default Libraries
#include<iostream>
#include<typeinfo>
#include<vector>
#include<string>

// Game Files
#include<Engine/WorldCreation/Fundamental Elements/Blocks.h>

/*
* The 16x16x16 Chunk implementation that is meant to be lightweight.
* I assume that the chunk coordinates are uniform top left corner of each chunk, 
* rest of the coordinates are derived from that If needed.
* This class has a field containing its ID, that is, a random generated 32 Bit hash code
* by which the chunk can be later recognized in the runtime and saved or modified
*/

// Macros for defining chunk constants

#define CHUNK_SIDE_LENGTH 16

//
//
//

class Chunk {
protected:

	// Chunk unique ID

	std::string m_Identifier;

	// Block data

	std::vector<std::unique_ptr<Block>> m_BlockData;

	// Chunk coordinates

	glm::vec3 m_Position;

	// Chunk state flags

	bool m_IsPositionSet = false;
	bool m_IsBlockDataGenerated = false;
	bool m_IsVisible = false;

public:

	// Constructors and a Virtual destructor 

	Chunk(void) : m_Identifier(), m_BlockData(), m_Position(glm::vec3(0.0f)) {};
	Chunk(glm::vec3 Position) : m_Identifier(), m_BlockData(), m_Position(Position) {};
	~Chunk(void) {};

	// Flag altering

	inline void EnablePositionFlag(void) { m_IsPositionSet = true; }
	inline void EnableBlockDataFlag(void) { m_IsBlockDataGenerated = true; }
	inline void EnableVisibilityFlag(void) { m_IsVisible = true; }
	//
	inline void DisablePositionFlag(void) { m_IsPositionSet = false; }
	inline void DisableBlockDataFlag(void) { m_IsBlockDataGenerated = false; }
	inline void DisableVisibilityFlag(void) { m_IsVisible = false; }

	// Methods for the chunk creating pipeline

	std::vector<std::unique_ptr<Block>>* GetBlockDataRefference(void);
	void SetBlockDataVector(void);

	// Methods for the chunk meshing pipeline

	bool CanBePassedFurther(void);

	// Identifying the chunk at runtime

	std::string GetChunkIdentifier(void);
	glm::vec3 GetChunkPosition(void);

};