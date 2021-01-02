/****************************************************************************/
/*!
\file
   Renderer.hpp
\Author
   Ryan Dugie
\brief
    Copyright (c) Ryan Dugie. All rights reserved.
    Licensed under the Apache License 2.0

    The core renderer class
*/
/****************************************************************************/

#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"

struct GLFWwindow;
typedef GLFWwindow* WindowPtr;

namespace OGL
{

    class Renderer
    {

    public:

        Renderer();
        ~Renderer();
        void Draw(float dt);
        WindowPtr Window() const;


    private:
        /* friends */
        friend static void FramebufferResizeCallback(WindowPtr window, int width, int height);

        /* Functions */
        void InitGLFW();
        void ShutdownGLFW();

        void InitWindow();
        void ShutdownWindow();

        void ReInitOGL();
        void InitOGL();
        void ShutdownOGL();

        void Present();

        // window
        WindowPtr mWindow = nullptr;
        int mWindowWidth = 800;
        int mWindowHeight = 800;
        int mVSync = 1;     
        bool mFramebufferResized = false;

        // scene
        OGL::Mesh mMesh;
        OGL::Shader mShader;
        glm::mat4 mProj = glm::mat4(1);
        glm::mat4 mView = glm::mat4(1);
        float mAngle = 0;
    };
}

#endif // RENDERER_HPP
