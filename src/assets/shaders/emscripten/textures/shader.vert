#version 130

in vec2 position;
in vec2 uv;

out vec2 uvOut;

// Camera Matrices
uniform mat4 combinedMatrix;
uniform mat4 modelMatrix;

void main(){
    uvOut = uv;

    gl_Position = combinedMatrix * modelMatrix * vec4(position, 0.0f, 1.0f);
}