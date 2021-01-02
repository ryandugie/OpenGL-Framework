/****************************************************************************/
/*!
\file
   Renderer.cpp
\Author
   Ryan Dugie
\brief
    Copyright (c) Ryan Dugie. All rights reserved.
    Licensed under the Apache License 2.0

    The core renderer class
*/
/****************************************************************************/
/*============================================================================*\
|| ------------------------------ INCLUDES ---------------------------------- ||
\*============================================================================*/

#include "OPENGLPCH.hpp"
#include "Renderer.hpp"

/*============================================================================*\
|| --------------------------- GLOBAL VARIABLES ----------------------------- ||
\*============================================================================*/


/*============================================================================*\
|| -------------------------- STATIC FUNCTIONS ------------------------------ ||
\*============================================================================*/

namespace OGL {
    /****************************************************************************/
    /*!
    \brief
      Callback for all GLFW errors

    \param error
      The GLFW error code

    \param description
      Error description
    */
    /****************************************************************************/
    static void GLFWErrorCallback(int error, const char* description)
    {
        DEBUG::log.Error("GLFW Error ", error, " : ", description);
    }

    /****************************************************************************/
    /*!
    \brief
      Callback for all OpenGL errors
    */
    /****************************************************************************/
    static void GLAPIENTRY GLMessageCallback(GLenum source, GLenum type, GLuint id,
            GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        if (severity == 33387)
        {
            return;
        }

        DEBUG::log.Error("GL Error: ", id, " | ", message);
    }

    /****************************************************************************/
    /*!
    \brief
      Called when our window gets resized,
      signal the renderer to resize its buffers

    \param window
      The window that got resized

    \param width
      The new width

    \param height
      The new height
    */
    /****************************************************************************/
    static void FramebufferResizeCallback(WindowPtr window, int width, int height)
    {
        OGL::Renderer* renderer = reinterpret_cast<OGL::Renderer*>(glfwGetWindowUserPointer(window));
        renderer->mFramebufferResized = true;
        renderer->mWindowWidth = width;
        renderer->mWindowHeight = height;
    }
}

/*============================================================================*\
|| -------------------------- PUBLIC FUNCTIONS ------------------------------ ||
\*============================================================================*/

/****************************************************************************/
/*!
\brief
  Initialize the renderer
*/
/****************************************************************************/
OGL::Renderer::Renderer()
{
    InitGLFW();
    InitOGL();
}

/****************************************************************************/
/*!
\brief
  Clean up
*/
/****************************************************************************/
OGL::Renderer::~Renderer()
{
    ShutdownGLFW();
    ShutdownOGL();
}

/****************************************************************************/
/*!
\brief
  Render

\param dt
  Delta-Time
*/
/****************************************************************************/
void OGL::Renderer::Draw(float dt)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mAngle -= dt;
    glm::mat4 mWorld = glm::mat4(1);
    mWorld = glm::rotate(mWorld, mAngle, { 0, 1, 0 } );

    mShader.Use();
    mShader.SetUniform("projection", mProj);
    mShader.SetUniform("view", mView);
    mShader.SetUniform("world", mWorld);
    mMesh.Draw();

    Present();
}

/****************************************************************************/
/*!
\brief
  Get the application window

\return
  Pointer to the window

*/
/****************************************************************************/
WindowPtr OGL::Renderer::Window() const
{
    return mWindow;
}

/*============================================================================*\
|| ------------------------- PRIVATE FUNCTIONS ------------------------------ ||
\*============================================================================*/

/****************************************************************************/
/*!
\brief
  Restart OGL
*/
/****************************************************************************/
void OGL::Renderer::ReInitOGL()
{
    ShutdownOGL();
    InitOGL();
}

/****************************************************************************/
/*!
\brief
  Initialize GLFW
*/
/****************************************************************************/
void OGL::Renderer::InitGLFW()
{
    glfwSetErrorCallback(OGL::GLFWErrorCallback);
    if (!glfwInit())
    {
        throw std::runtime_error("GLFW: glfwInit() failed!\n");
    }

    // create the GLFW window
    InitWindow();
}

/****************************************************************************/
/*!
\brief
  Create the application window
*/
/****************************************************************************/
void OGL::Renderer::InitWindow()
{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "OGL-Framework", nullptr, nullptr);
    if (mWindow == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("GLFW: glfwCreateWindow() failed!\n");
    }
    glfwMakeContextCurrent(mWindow);
    glViewport(0, 0, mWindowWidth, mWindowHeight);
    glfwSetFramebufferSizeCallback(mWindow, OGL::FramebufferResizeCallback);
}


/****************************************************************************/
/*!
\brief
  All OpenGL related initilaization
*/
/****************************************************************************/
void OGL::Renderer::InitOGL()
{
   glewInit();
   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);

#ifdef _DEBUG
   glEnable(GL_DEBUG_OUTPUT);
   glDebugMessageCallback(GLMessageCallback, 0);
#endif

   mMesh.Create("../Resource/Models/StanfordBunny.obj");
   mShader.Create("../Resource/Shaders/Simple.vert", "../Resource/Shaders/Simple.frag");

   float y = 0.1f;
   glm::vec3 position = { 0, y, 1 };
   glm::vec3 up = { 0, 1, 0 };
   float fov = 0.42173f;
   float aspectRatio = float(mWindowWidth) / mWindowHeight;
   float nearPlane = 0.1f;
   float farPlane = 250.f;

   mProj = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
   mView = glm::lookAt(position, glm::vec3(0.0f, y, 0.0f), up);
}

/****************************************************************************/
/*!
\brief
  all GLFW related cleanup
*/
/****************************************************************************/
void OGL::Renderer::ShutdownGLFW()
{
    ShutdownWindow();
    glfwTerminate();
}

/****************************************************************************/
/*!
\brief
  destroy the application window
*/
/****************************************************************************/
void OGL::Renderer::ShutdownWindow()
{
    glfwDestroyWindow(mWindow);
}

/****************************************************************************/
/*!
\brief
  All OpenGL related clean up
*/
/****************************************************************************/
void OGL::Renderer::ShutdownOGL()
{

}

/****************************************************************************/
/*!
\brief
  Present the swapchain
*/
/****************************************************************************/
void OGL::Renderer::Present()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}