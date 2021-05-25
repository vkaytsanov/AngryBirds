#version 330 core

layout (location = 0) in vec2 vertices;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec2 position;
layout (location = 3) in vec2 size;


out DATA{
    vec2 uv;
} vertices_out;

// Projection Matrix
uniform mat4 projView;

void main(){
    gl_Position = projView * vec4(position + vertices, 0.0f, 1.0f);
    vertices_out.uv = uv;
}