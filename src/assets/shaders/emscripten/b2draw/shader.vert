#version 300 es 

in vec2 position;
in vec4 colour;

out vec4 fsColour;
uniform mat4 MVP;

void main() {
	gl_Position =  MVP * vec4(position.x, position.y, 0, 1);
	fsColour = colour;
}
