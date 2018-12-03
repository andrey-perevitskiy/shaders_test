#version 330 core

in vec3 flat_fragment_color;

out vec3 flat_color;

void main(void) {
	flat_color = flat_fragment_color;
}
