#pragma once

#include<glm.hpp>

/*
* This file contains the basis for the polimorphic block system, 
* with the main class Block, that has all of the needed variables
* to enable the OpenGL "Material" functionality
*/

struct Material {

	// Variables needed for the material functionality

	glm::vec3 m_Ambient = glm::vec3(0.0f);
	glm::vec3 m_Diffuse = glm::vec3(0.0f);
	glm::vec3 m_Specular = glm::vec3(0.0f);
	float m_Shininess = 0.0f;

	// Overloaded "=" operator for quick value pushing

	Material& operator=(const Material& material) {

		//Copying the data
		this->m_Ambient = material.m_Ambient;
		this->m_Diffuse = material.m_Diffuse;
		this->m_Specular = material.m_Specular;
		this->m_Shininess = material.m_Shininess;

		//Returning the finished object
		return *this;
	}

};

class Block {
protected:

	// variable for the material properties

	Material m_Material;

	// Block attributes

	bool m_Destroyable;
	bool m_Liquid;
	int m_Toughness; //Scale from 1 to 3, 1 means no extra tools needed to pick up.

public:

	// Constructors and a virtual destructor

	Block(): m_Destroyable(false), m_Liquid(false), m_Toughness(0), m_Material({glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), 0.0f}) {};
	Block(Material value) : m_Destroyable(false), m_Liquid(false), m_Toughness(0), m_Material(value) {};
	virtual ~Block() {};

	// Polimorphic getters and setters

	virtual void inline SetMaterial(Material value) { m_Material = value; };
	virtual Material inline GetMaterial(void) { return m_Material; };
	virtual void inline SetToughness(int value) { if (value >= 0 && value <= 3) { m_Toughness = value; } };
	virtual int inline GetToughness(void) { return m_Toughness; };

	// Flag manipulation

	virtual void inline ActivateDestroyable(void) { m_Destroyable = true; };
	virtual void inline DisactivateDestroyable(void) { m_Destroyable = false; };
	virtual void inline ActivateLiquid(void) { m_Liquid = true; };
	virtual void inline DisactivateLiquid(void) { m_Liquid = false; };

	// Flags values access

	virtual bool inline Destroyable(void) { return m_Destroyable; };
	virtual bool inline Liquid(void) { return m_Liquid; };

};