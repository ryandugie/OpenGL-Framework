/****************************************************************************/
/*!
\file
   Main.cpp
\Author
   Ryan Dugie
\brief
    Copyright (c) Ryan Dugie. All rights reserved.
    Licensed under the Apache License 2.0
*/
/****************************************************************************/

/*============================================================================*\
|| ------------------------------ INCLUDES ---------------------------------- ||
\*============================================================================*/

#include "OPENGLPCH.hpp"
#include "Shader.hpp"
#include <fstream>
#include <streambuf>

/*============================================================================*\
|| --------------------------- GLOBAL VARIABLES ----------------------------- ||
\*============================================================================*/

#define INFOLOGSIZE 512

/*============================================================================*\
|| -------------------------- STATIC FUNCTIONS ------------------------------ ||
\*============================================================================*/

/*============================================================================*\
|| -------------------------- PUBLIC FUNCTIONS ------------------------------ ||
\*============================================================================*/

/****************************************************************************/
/*!
\brief
  Clean up
*/
/****************************************************************************/
OGL::Shader::~Shader()
{
    glDeleteProgram(mID);
}

/****************************************************************************/
/*!
\brief
  Load, compile, and link the shaders

\param vertexShader
  The path to the vertex shader

\param fragmentShader
  The path to the fragment shader
*/
/****************************************************************************/
void OGL::Shader::Create(const std::string vertexShader, const std::string fragmentShader)
{ 
    /* vertex shader */
    GLuint vertexShaderID = LoadShader(vertexShader, GL_VERTEX_SHADER);

    /* fragment shader */
    GLuint fragmentShaderID = LoadShader(fragmentShader, GL_FRAGMENT_SHADER);

    /* create program */
    mID = glCreateProgram();
    glAttachShader(mID, vertexShaderID);
    glAttachShader(mID, fragmentShaderID);
    glLinkProgram(mID);
    int  success;
    glGetProgramiv(mID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[INFOLOGSIZE];
        glGetProgramInfoLog(mID, INFOLOGSIZE, NULL, infoLog);
        throw std::runtime_error("shader linkage failed! " + std::string(infoLog));
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

/****************************************************************************/
/*!
\brief
  Bind this shader program
*/
/****************************************************************************/
void OGL::Shader::Use()
{
    glUseProgram(mID);
}

/****************************************************************************/
/*!
\brief
  Set a uniform bool

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, bool value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

/****************************************************************************/
/*!
\brief
  Set a uniform int

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, int value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

/****************************************************************************/
/*!
\brief
  Set a uniform float

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, float value) const
{
    glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

/****************************************************************************/
/*!
\brief
  Set a uniform vec2

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, const glm::vec2 value) const
{
    glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

/****************************************************************************/
/*!
\brief
  Set a uniform vec2

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
}

/****************************************************************************/
/*!
\brief
  Set a uniform vec3

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, const glm::vec3 value) const
{
    glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

/****************************************************************************/
/*!
\brief
  Set a uniform vec3

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
}

/****************************************************************************/
/*!
\brief
  Set a uniform vec4

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, const glm::vec4 value) const
{
    glUniform4fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

/****************************************************************************/
/*!
\brief
  Set a uniform vec4

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(mID, name.c_str()), x, y, z, w);
}

/****************************************************************************/
/*!
\brief
  Set a uniform mat2

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, const glm::mat2 mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/****************************************************************************/
/*!
\brief
  Set a uniform mat3

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, const glm::mat3 mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/****************************************************************************/
/*!
\brief
  Set a uniform mat4

\param name
  Name of the uniform in the shader

\param value
  The value we want to send to the shader
*/
/****************************************************************************/
void OGL::Shader::SetUniform(const std::string name, const glm::mat4 mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/*============================================================================*\
|| ------------------------- PRIVATE FUNCTIONS ------------------------------ ||
\*============================================================================*/

/****************************************************************************/
/*!
\brief
  Load and compile a shader

\param path
  The path to the shader

\param type
  What kind of shader to compile. IE: vertex or fragment

*/
/****************************************************************************/
GLuint OGL::Shader::LoadShader(const std::string path, const int type)
{
    /* load */
    std::ifstream file(path);
    std::string temp((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const char* code = temp.c_str();

    /* compile */
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    int  success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[INFOLOGSIZE];
        glGetShaderInfoLog(shader, INFOLOGSIZE, NULL, infoLog);
        throw std::runtime_error("shader compilation failed! " + std::string(infoLog));
    }
    return shader;
}
