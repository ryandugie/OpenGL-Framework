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
#ifndef MESH_H
#define MESH_H
#pragma once

#include "OPENGLPCH.hpp"

#pragma warning(push)
#pragma warning(disable : 26812 26495 26451)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

namespace OGL 
{

    struct Vertex 
    {
        glm::vec4 position = glm::vec4(0);
        glm::vec4 normal = glm::vec4(0);
    };

    class Mesh 
    {
    public:
        ~Mesh();
        Mesh() = default;
        void Create(std::string path);

        void Draw();

    private:
        void GetMesh(aiMesh* mesh);

        GLuint mVBO = 0;
        GLuint mVAO = 0;
        GLuint mIBO = 0;

        std::vector<Vertex> mVertices;
        std::vector<GLuint> mIndices;
    };
}

#endif
