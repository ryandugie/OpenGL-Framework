/****************************************************************************/
/*!
\file
   Mesh.hpp
\Author
   Ryan Dugie
\brief
    Copyright (c) Ryan Dugie. All rights reserved.
    Licensed under the Apache License 2.0
*/
/****************************************************************************/
#ifndef SHADER_H
#define SHADER_H
#pragma once

#include "OPENGLPCH.hpp"

namespace OGL
{
    class Shader
    {
    public:
        ~Shader();
        Shader() = default;
        void Create(const std::string vertexShader, const std::string fragmentShader);

        void Use();

        void SetUniform(const std::string name, bool value) const;
        void SetUniform(const std::string name, int value) const;
        void SetUniform(const std::string name, float value) const;
        void SetUniform(const std::string name, const glm::vec2 value) const;
        void SetUniform(const std::string name, float x, float y) const;
        void SetUniform(const std::string name, const glm::vec3 value) const;
        void SetUniform(const std::string name, float x, float y, float z) const;
        void SetUniform(const std::string name, const glm::vec4 value) const;
        void SetUniform(const std::string name, float x, float y, float z, float w);
        void SetUniform(const std::string name, const glm::mat2 mat) const;
        void SetUniform(const std::string name, const glm::mat3 mat) const;
        void SetUniform(const std::string name, const glm::mat4 mat) const;

    private:

        GLuint LoadShader(const std::string shader, const int type);

        GLuint mID = 0;
    };
}

#endif
