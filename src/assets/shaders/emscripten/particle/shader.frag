#version 130

out vec4 color;

uniform sampler2D tex_id;


in vec2 uvOut;

void main() {
    color = texture(tex_id, uvOut);
}