#version 450 core
layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aNormal;

layout (location = 0) out vec4 normal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    normal = normalize(aNormal);   
    gl_Position = projection * view * world * aPosition;
}