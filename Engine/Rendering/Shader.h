#pragma once

/*
* Standard libraries
*/

#include<string>
#include<sstream>
#include<unordered_map>
#include<iostream>
#include<fstream>

/*
* Custom 3D Libraries
*/

#include<glm.hpp>
#include<glad/glad.h>
#include<glfw3.h>
#include<glfw3native.h>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
protected:
	std::string m_FilePath;
	unsigned int m_RendererID;
	/*Caching for uniforms*/
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	/*Set uniforms*/

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name) const;
	unsigned int CreateShaders(const std::string& vertexShaders, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int shader_type, const std::string& shader_source);

	ShaderProgramSource ParseShader(const std::string& filepath);
};

