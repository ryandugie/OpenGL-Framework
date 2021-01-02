#version 450 core

layout (location = 0) in vec4 normal;
out vec4 color;

void main()
{  
  color = normal;
}