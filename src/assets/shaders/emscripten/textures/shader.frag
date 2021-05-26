#version 300 es 
precision mediump float;

uniform sampler2D tex_id;

in vec2 uvOut;
out vec4 color;


void main() {
    color = texture(tex_id, uvOut);
}