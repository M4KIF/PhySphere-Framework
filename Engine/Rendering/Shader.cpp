#include "Shader.h"


#include "Shader.h"

Shader::Shader(const std::string& filepath)
    : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShaders(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                //Set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                //Set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            /*This code has some error handling in it, helps the code not to reach out for stringstream[-1] and cause madness*/

            if (type == ShaderType::VERTEX || type == ShaderType::FRAGMENT)
                ss[(int)type] << line << '\n';

            /*Using the shader type as an index to the stringstream array, neat little trick here*/
        }
    }

    /*I have to address this type and learn more about it than I was given at the classes. Quite an useful bastard.
    This returns the set struct with the fields filled up with the shaders source code*/

    return { ss[0].str(), ss[1].str() };
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

unsigned int Shader::CompileShader(unsigned int shader_type, const std::string& shader_source)
{
    /*The making procedure of the shader program for further use*/

    unsigned int id = glCreateShader(shader_type);
    const char* source = &shader_source[0];
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    /*Making a short error handling code part*/

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        /*Shader hasn't compiled correctly, time to retrieve the error message*/
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); // This function is used to allocate dynamically on the stack.
        glGetShaderInfoLog(id, length, &length, message);

        /*This code I must finally analyse thoroughly, tis type of condensing the if statement into one line
        is something that I am after.*/

        std::cout << "Failed to compile the " << (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    /*Returning the ID of the freshly compiled shader program*/

    return id;

}

unsigned int Shader::CreateShaders(const std::string& vertexShaders, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaders); //Calling the function to compile the vertex program
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); //Calling the function to compile the fragment program

    glAttachShader(program, vs); //Attach the compiled vertex shader to the program
    glAttachShader(program, fs); //Attach the compiled fragment shader to the program
    glLinkProgram(program); //Link the files
    glValidateProgram(program);

    /*Detaches the compiled source code from the program as it is not needed anymore*/

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    /*Deletes the shader part programs*/

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;      //of having those variables and objects written without order. To read the DOCS on Cplusplus*/
    m_UniformLocationCache[name] = location; /*This is a more advanced STL container, that gives the possibility*/
    return location;
}
