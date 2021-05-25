#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out DATA{
    vec2 uv;
} vertices_out;

// Camera Matrices
uniform mat4 combinedMatrix;
uniform mat4 modelMatrix;

void main(){
    vertices_out.uv = uv;

    gl_Position = combinedMatrix * modelMatrix * vec4(position, 0.0f, 1.0f);
}