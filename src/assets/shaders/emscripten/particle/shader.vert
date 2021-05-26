#version 300 es 

in vec2 vertices;
in vec2 uv;
in vec2 position;
in vec2 size;

out vec2 uvOut;

// Projection Matrix
uniform mat4 projView;

void main(){
    gl_Position = projView * vec4(position + vertices, 0.0f, 1.0f);
    uvOut = uv;
}