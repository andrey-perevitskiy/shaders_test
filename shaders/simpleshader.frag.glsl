#version 330 core

in vec3 fragment_color;

out vec3 color;

void main(void) {
	color = fragment_color;
}
