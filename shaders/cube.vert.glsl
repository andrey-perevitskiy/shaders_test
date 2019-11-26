#version 330 core

uniform mat4 cube_trans;

layout(location = 0) in vec3 cube_pos;
layout(location = 1) in vec3 cube_vertex_color;

out vec3 cube_fragment_color;

void main(void) {
    gl_Position = cube_trans * vec4(cube_pos, 1.0);
    cube_fragment_color = cube_vertex_color;
}
