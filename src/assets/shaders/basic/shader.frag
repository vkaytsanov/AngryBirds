#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

in vec3 fragmentColor;
out vec4 color;


void main() {
    color = vec4(fragmentColor, 1);
}