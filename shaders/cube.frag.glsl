#version 330 core

in vec3 cube_fragment_color;

out vec3 cube_color;

void main(void) {
    cube_color = cube_fragment_color;
}
